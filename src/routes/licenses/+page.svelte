<script lang="ts">
    import { onMount } from "svelte";

    const LICENSES_JSON_PATH = "/oss-licenses.json";

    type LicensesJson = Record<string, string>[];
    let licensesJson: LicensesJson = $state([]);
    onMount(() =>
        fetch(LICENSES_JSON_PATH)
            .then((response) => {
                if (response.ok) {
                    return response.json();
                } else {
                    throw new Error("failed to fetch licenses");
                }
            })
            .then((json: LicensesJson) => {
                licensesJson = json;
            })
            .catch(console.warn),
    );
</script>

<svelte:head>
    <title>OSS Licenses | Hitomezashi</title>
    <link
        rel="preload"
        href={LICENSES_JSON_PATH}
        type="application/json"
        as="fetch"
        crossorigin="anonymous"
    />
</svelte:head>

<header>
    <a href="/">&lt; home</a>
</header>

<main>
    <p>Get the <a href={LICENSES_JSON_PATH}>license info as JSON</a>.</p>
    {#each licensesJson as licenseInfo}
        <div>
            <h2>{licenseInfo.name} (<span class="repo">{licenseInfo.repository}</span>)</h2>
            <pre>{licenseInfo.licenseText}</pre>
        </div>
        <hr />
    {/each}
</main>

<style>
    header,
    main {
        width: 90%;
        margin: 0 auto;
    }

    .repo {
        font-family: monospace;
    }
    
    pre {
        white-space: pre-wrap;
    }
</style>
