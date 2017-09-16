#include <vector>
#include <string>
#include <array>
#include <cstdio>
#include <ospray/ospray.h>

struct Atom {
	float x, y, z;
	int atom_type;

	Atom(float x, float y, float z, int type)
		: x(x), y(y), z(z), atom_type(type)
	{}
};

void write_ppm(const std::string &file_name, const int width, const int height,
		const uint32_t *img);

int main(int argc, const char **argv) {
	OSPError err = ospInit(&argc, argv);
	if (err != OSP_NO_ERROR) {
		return 1;
	}

	// Setup our particle data as a sphere geometry.
	// Each particle is an x,y,z center position + an atom type id, which
	// we'll use to apply different colors for the different atom types.
	std::vector<Atom> atoms = {
		Atom(1.0, 0.0, 0.0, 0),
		Atom(0.5, 0.5, 0.0, 1),
		Atom(0.0, 1.0, 0.0, 0),
		Atom(-0.5, 0.5, 0.0, 2),
		Atom(-1.0, 0.0, 0.0, 1),
		Atom(-0.5, -0.5, 0.0, 2),
		Atom(0.0, -1.0, 0.0, 0),
		Atom(0.5, -0.5, 0.0, 1)
	};
	std::vector<float> atom_colors = {
		1.0, 0.0, 0.0,
		0.0, 1.0, 0.0,
		0.0, 0.0, 1.0
	};

	// Make the OSPData which will refer to our particle and color data.
	// The OSP_DATA_SHARED_BUFFER flag tells OSPRay not to share our buffer,
	// instead of taking a copy.
	OSPData sphere_data = ospNewData(atoms.size() * sizeof(Atom), OSP_CHAR,
			atoms.data(), OSP_DATA_SHARED_BUFFER);
	OSPData color_data = ospNewData(atom_colors.size(), OSP_FLOAT3,
			atom_colors.data(), OSP_DATA_SHARED_BUFFER);

	// Create the sphere geometry that we'll use to represent our particles
	OSPGeometry spheres = ospNewGeometry("spheres");
	ospSetData(spheres, "spheres", sphere_data);
	ospSetData(spheres, "color", color_data);
	ospSet1f(spheres, "radius", 0.35);
	// Tell OSPRay how big each particle is in the atoms array, and where
	// to find the color id. The offset to the center position of the sphere
	// defaults to 0.
	ospSet1f(spheres, "bytes_per_sphere", sizeof(Atom));
	ospSet1i(spheres, "offset_colorID", 3 * sizeof(float));

	// Our sphere data is now finished being setup, so we commit it to tell
	// OSPRay all the object's parameters are updated.
	ospCommit(spheres);

	// Create the model we'll place all our scene geometry into, representing
	// the world to be rendered.
	OSPModel model = ospNewModel();
	ospAddGeometry(model, spheres);
	ospCommit(model);

	// Setup the camera we'll render the scene from
	const osp::vec2i img_size{1024, 1024};
	const std::array<float, 3> cam_pos = {0.0, 0.0, 4.0};
	const std::array<float, 3> cam_up = {0.0, 1.0, 0.0};
	const std::array<float, 3> cam_dir = {0.0, 0.0, -1.0};
	OSPCamera camera = ospNewCamera("perspective");
	ospSet1f(camera, "aspect", 1.0);
	ospSet3fv(camera, "pos", cam_pos.data());
	ospSet3fv(camera, "up", cam_up.data());
	ospSet3fv(camera, "dir", cam_dir.data());
	ospCommit(camera);

	// We'll use the scivis renderer, this renderer computes ambient occlusion
	// and shadows for enhanced depth cues
	OSPRenderer renderer = ospNewRenderer("scivis");

	// Create and setup an ambient light, this will also compute ambient
	// occlusion.
	OSPLight light = ospNewLight(renderer, "ambient");
	ospCommit(light);
	// Setup a list of all the lights in the scene we're rendering
	OSPData lights = ospNewData(1, OSP_LIGHT, &light, 0);
	ospCommit(lights);

	// Setup the parameters for the renderer
	ospSet1i(renderer, "aoSamples", 8);
	ospSet1f(renderer, "bgColor", 1.0);
	ospSetObject(renderer, "model", model);
	ospSetObject(renderer, "lights", lights);
	ospSetObject(renderer, "camera", camera);
	ospCommit(renderer);

	// Create a framebuffer to render the image too
	OSPFrameBuffer framebuffer = ospNewFrameBuffer(img_size, OSP_FB_SRGBA, OSP_FB_COLOR);
	ospFrameBufferClear(framebuffer, OSP_FB_COLOR);

	// Render the image and save it out
	ospRenderFrame(framebuffer, renderer, OSP_FB_COLOR);

	const uint32_t *img = static_cast<const uint32_t*>(ospMapFrameBuffer(framebuffer, OSP_FB_COLOR));
	write_ppm("simple_particles.ppm", img_size.x, img_size.y, img);
	ospUnmapFrameBuffer(img, framebuffer);

	// Clean up all our objects
	ospFreeFrameBuffer(framebuffer);
	ospRelease(renderer);
	ospRelease(lights);
	ospRelease(renderer);
	ospRelease(camera);
	ospRelease(model);
	ospRelease(spheres);

	return 0;
}

void write_ppm(const std::string &file_name, const int width, const int height,
		const uint32_t *img)
{
	FILE *file = fopen(file_name.c_str(), "wb");
	if (!file) {
		throw std::runtime_error("Failed to open file for PPM output");
	}

	fprintf(file, "P6\n%i %i\n255\n", width, height);
	std::vector<uint8_t> out(3 * width, 0);
	for (int y = 0; y < height; ++y) {
		const uint8_t *in = reinterpret_cast<const uint8_t*>(&img[(height - 1 - y) * width]);
		for (int x = 0; x < width; ++x) {
			out[3 * x] = in[4 * x];
			out[3 * x + 1] = in[4 * x + 1];
			out[3 * x + 2] = in[4 * x + 2];
		}
		fwrite(out.data(), out.size(), sizeof(uint8_t), file);
	}
	fprintf(file, "\n");
	fclose(file);
}

