<script lang="ts">
    import type { Vec2 } from "$lib";

    let {
        pattern,
        spacing,
    }: {
        pattern: Vec2<boolean[]>;
        spacing: number;
    } = $props();

    let svgEl: SVGElement;
    export const getInnerSvg = (): string => svgEl.outerHTML;
</script>

{#snippet line(
    i: number,
    hasCrossOffset: boolean,
    crossCount: number,
    along: "x" | "y",
)}
    {@const mainOffset = i * spacing + 0.5}
    {@const positions = [
        mainOffset,
        hasCrossOffset ? spacing : 0,
        mainOffset,
        crossCount * spacing,
    ]}

    {@const shift = along === "x" ? 0 : 1}
    <line
        x1={positions[0 + shift]}
        y1={positions[1 + shift]}
        x2={positions[2 + shift]}
        y2={positions[(3 + shift) % 4]}
        stroke-dasharray={`${spacing + 1} ${spacing - 1}`}
    ></line>
{/snippet}

<svg
    xmlns="http://www.w3.org/2000/svg"
    viewBox="0 0 {pattern.x.length * spacing} {pattern.y.length * spacing}"
    shape-rendering="crispEdges"
    bind:this={svgEl}
>
    <rect width="100%" height="100%" fill="white" />

    {#each pattern.x as hasXOffset, x_i}
        {@render line(x_i, hasXOffset, pattern.y.length, "x")}
    {/each}
    {#each pattern.y as hasYOffset, y_i}
        {@render line(y_i, hasYOffset, pattern.x.length, "y")}
    {/each}

    <style>
        line {
            stroke: black;
        }
    </style>
</svg>

<style>
    svg {
        height: 100%;
        width: 100%;
    }
</style>
