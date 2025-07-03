<script lang="ts">
    import type { Vec2 } from "$lib";
    import Hitomezashi from "./Hitomezashi.svelte";
    import PatternInput from "./PatternInput.svelte";

    const PATTERN_INITIAL = {
        x: Array(5).fill(false),
        y: [false, true, false, true, false],
    };

    let spacing = $state(5);
    let pattern: Vec2<boolean[]> = $state(PATTERN_INITIAL);
    let hitomezashiComponent: Hitomezashi;
</script>

<div class="outerContainer">
    <div class="topInputContainer">
        <label
            >spacing: <input
                type="number"
                bind:value={spacing}
                min="2"
                max="100"
            /></label
        >
        <span>
            <!-- TODO: implement -->
            <input type="button" value="export" />
            <input type="button" value="load" />
            <input
                type="button"
                value="reset"
                onclick={() => {
                    pattern = PATTERN_INITIAL;
                }}
            />
        </span>
    </div>
    <div class="patternInputContainer">
        <PatternInput bind:pattern={pattern.x} axisName="x"></PatternInput>
        <PatternInput bind:pattern={pattern.y} axisName="y"></PatternInput>
    </div>
    <div class="hitomezashiComponentContainer">
        <Hitomezashi {pattern} {spacing} bind:this={hitomezashiComponent}
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
                linkEl.setAttribute("download", `hitomezashi-${Math.trunc(Date.now() / 1000)}.svg`);
                document.body.appendChild(linkEl);
                linkEl.click();
                document.body.removeChild(linkEl);
                URL.revokeObjectURL(linkEl.href);
            }}
        />
    </div>
</div>

<style>
    div.outerContainer {
        display: flex;
        flex-direction: column;
        height: 100svh;
        align-items: center;
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
