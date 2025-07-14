import { createViteLicensePlugin } from 'rollup-license-plugin';
import { defineConfig } from 'vite';
import { sveltekit } from '@sveltejs/kit/vite';

export default defineConfig({
	plugins: [
		sveltekit(),
		createViteLicensePlugin({
			includePackages: () => [__dirname]
		}),
	],
	define: {
		__REPO_URL__: JSON.stringify("https://github.com/arjunsatarkar/hitomezashi")
	}
});
