<script lang="ts">
    import Hitomezashi from "./Hitomezashi.svelte";
    import PatternInput from "./PatternInput.svelte";
    import type { Pattern, XYPattern } from "$lib";

    import { onMount, tick } from "svelte";
    import { page } from "$app/state";
    import { replaceState } from "$app/navigation";

    const INITIAL_STATE: { pattern: XYPattern; spacing: number } = {
        pattern: {
            x: Array(5).fill(false),
            y: [false, true, false, true, false],
        },
        spacing: 5,
    };

    let hitomezashiState = $state(structuredClone(INITIAL_STATE));
    let oldState: typeof hitomezashiState | null = $state(null);
    let hitomezashiComponent: Hitomezashi;

    const serializePattern = (pattern: Pattern): string => {
        const bytes = Math.ceil(pattern.length / 8);
        const binstring = pattern
            .map((v) => (v ? "1" : "0"))
            .join("")
            .padEnd(bytes * 8, "0");
        const arr: number[] = [];
        for (let i = 0; i < pattern.length; i += 8) {
            arr.push(parseInt(binstring.slice(i, i + 8), 2));
        }

        return pattern.length + ";" + btoa(String.fromCharCode(...arr));
    };

    const deserializePattern = (patternStr: string): Pattern => {
        const [lengthStr, patternB64] = patternStr.split(";");
        const length = +lengthStr;
        return [...atob(patternB64)]
            .flatMap((c) => [...c.charCodeAt(0).toString(2).padStart(8, "0")])
            .map((v) => (+v ? true : false))
            .slice(0, length);
    };

    onMount(() => {
        const searchParams = new URLSearchParams(window.location.search);

        const xParam = searchParams.get("x");
        const yParam = searchParams.get("y");
        if (xParam && yParam) {
            hitomezashiState.pattern.x = deserializePattern(xParam);
            hitomezashiState.pattern.y = deserializePattern(yParam);
        }

        const spacingParam = searchParams.get("s");
        if (spacingParam) {
            hitomezashiState.spacing = +spacingParam;
        }
    });

    $effect(() => {
        const url = new URL(location.origin + location.pathname);
        url.searchParams.set("x", serializePattern(hitomezashiState.pattern.x));
        url.searchParams.set("y", serializePattern(hitomezashiState.pattern.y));
        url.searchParams.set("s", hitomezashiState.spacing.toString());

        /*  Use SvelteKit replaceState, not navigator.replaceState, because
            it gives us warnings otherwise. The tick() is necessary for
            something or other to be initialized so this call works.
            https://github.com/sveltejs/kit/issues/11466
        */
        tick().then(() => replaceState(url, page.state));
    });
</script>

<svelte:head>
    <title>Hitomezashi</title>
</svelte:head>

<div class="outerContainer">
    <noscript>JavaScript is required to use this site.</noscript>
    <div class="inputContainer">
        <div class="mainInputContainer">
            <div class="topInputContainer">
                <label
                    >spacing: <input
                        type="number"
                        bind:value={hitomezashiState.spacing}
                        min="2"
                        max="100"
                    /></label
                >
            </div>
            <div class="patternInputContainer">
                <PatternInput
                    bind:pattern={hitomezashiState.pattern.x}
                    axisName="x"
                ></PatternInput>
                <PatternInput
                    bind:pattern={hitomezashiState.pattern.y}
                    axisName="y"
                ></PatternInput>
            </div>
        </div>
        <div class="extraInputContainer">
            <input
                type="button"
                value="copy link"
                onclick={() => {
                    navigator.clipboard.writeText(window.location.href);
                }}
            />
            <input
                type="button"
                value="swap x/y"
                onclick={() => {
                    [hitomezashiState.pattern.x, hitomezashiState.pattern.y] = [
                        hitomezashiState.pattern.y,
                        hitomezashiState.pattern.x,
                    ];
                }}
            />
            <input
                type="button"
                value="reset"
                onclick={() => {
                    oldState = hitomezashiState;
                    hitomezashiState = structuredClone(INITIAL_STATE);
                }}
            />
            <input
                type="button"
                value="undo reset"
                onclick={() => {
                    if (oldState !== null) {
                        hitomezashiState = oldState;
                        oldState = null;
                    }
                }}
            />
        </div>
    </div>
    <div class="hitomezashiComponentContainer">
        <Hitomezashi
            pattern={hitomezashiState.pattern}
            spacing={hitomezashiState.spacing}
            bind:this={hitomezashiComponent}
        ></Hitomezashi>
    </div>
    <div>
        <input
            type="button"
            value="Download SVG"
            onclick={() => {
                const linkEl = document.createElement("a");
                linkEl.href = URL.createObjectURL(
                    new Blob([hitomezashiComponent.getInnerSvg()], {
                        type: "image/svg+xml",
                    }),
                );
                linkEl.setAttribute(
                    "download",
                    `hitomezashi-${Math.trunc(Date.now() / 1000)}.svg`,
                );
                document.body.appendChild(linkEl);
                linkEl.click();
                document.body.removeChild(linkEl);
                URL.revokeObjectURL(linkEl.href);
            }}
        />
    </div>
</div>

<hr />

<style>
    div.outerContainer {
        display: flex;
        flex-direction: column;
        height: 100svh;
        align-items: center;
        row-gap: 1rem;
    }

    div.inputContainer {
        display: flex;
        flex-flow: row wrap;
        align-items: center;
        column-gap: 1rem;
    }

    div.extraInputContainer {
        display: flex;
        flex-direction: column;
    }

    div.topInputContainer {
        display: flex;
        flex-flow: row wrap;
        justify-content: center;
        column-gap: 1rem;
    }

    div.hitomezashiComponentContainer {
        flex-grow: 1;
        min-height: 0;
        min-width: 0;
    }
</style>
