<script lang="ts">
    let { children } = $props();
    import "$lib/index.css";
</script>

{@render children()}

<footer>
  <small>
    &copy; 2025-present <a href="https://arjunsatarkar.net">Arjun Satarkar.</a
    ><br />
    get the <a href={__REPO_URL__}>source code</a>&nbsp;| <a href="/oss-licenses.json">third-party licenses (json)</a>
  </small>
</footer>
