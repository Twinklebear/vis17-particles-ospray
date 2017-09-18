// C-callable functions are exported from ISPC with the export keyword.
// These act as scalar-code entry points to the ISPC code.
export void multiply(const uniform float *uniform a, const uniform float *uniform b,
		uniform float *uniform out, const uniform int nvals)
{
	print("program indices: %\n", programIndex);
	// Vectorizing is done through vectorized loop constructs such as
	// foreach. This construct maps the iterations of the for loop to
	// the vector lanes of the CPU for parallelism.
	foreach (i = 0 ... nvals) {
	print("program indices: %\n", programIndex);
		out[i] = a[i] * b[i];
	}
}

