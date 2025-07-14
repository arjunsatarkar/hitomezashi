<script lang="ts">
    import type { Pattern } from "$lib";

    let {
        pattern = $bindable(),
        axisName,
    }: { pattern: Pattern; axisName: "x" | "y" } = $props();
</script>

<fieldset>
    <legend>{axisName} pattern</legend>
    {#each pattern as _, i}
        <input type="checkbox" bind:checked={pattern[i]} />
    {/each}
    ({pattern.length})
    <div class="addRemoveButtons">
        <button onclick={() => pattern.pop()}>-</button>
        <button onclick={() => pattern.push(false)}>+</button>
    </div>
</fieldset>

<style>
    input[type="checkbox"] {
        width: 1rem;
        height: 1rem;
    }

    input[type="checkbox"] {
        appearance: none;
        background-color: lightgray;
    }

    input[type="checkbox"]:checked {
        background-color: black;
    }

    .addRemoveButtons {
        display: flex;
        flex-direction: row;
        justify-content: center;
        column-gap: 1rem;
    }

    .addRemoveButtons > button {
        padding: 0;
        border: 0;
        font-size: 1.5rem;
        background-color: transparent;
    }

    .addRemoveButtons > button:active {
        background-color: #00000055;
    }
</style>
