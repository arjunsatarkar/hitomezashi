import { createViteLicensePlugin } from 'rollup-license-plugin';
import { defineConfig } from 'vite';
import { sveltekit } from '@sveltejs/kit/vite';

import { homepage } from './package.json';

export default defineConfig({
	plugins: [
		sveltekit(),
		createViteLicensePlugin({
			includePackages: () => [__dirname]
		}),
	],
	define: {
		__APP_HOME__: JSON.stringify(homepage),
		__REPO_URL__: JSON.stringify("https://github.com/arjunsatarkar/hitomezashi")
	}
});
