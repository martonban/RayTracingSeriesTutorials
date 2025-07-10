#ifndef PRESET_H
#define PRESET_H

enum Presets {
	POOR,					// Mainly for test (low resolution, 100 samples, 30 depth)
	PERFORMANCE,			// Mainly for test (higher resolution, 100 samples, 40 depth)
	BALANCED,				// Good Results (FULL HD, 500 samples, 50 detph)
	BEAUTY,					// Good Quality Image (FULL HD, 1000 samples, 50 depth)
	FIDELITY				// ABSOLUTE CINEMA (4K, 1000 samples, 100 depth)
};

#endif
