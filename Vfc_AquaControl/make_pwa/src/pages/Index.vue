<template>
  <q-page class="flex flex-center">
    <q-select
      stack-label="Language"
      :options="[
        { label: 'Brazilian portuguese', value: 'pt-br' },
        { label: 'English (US)',         value: 'en-us' }
      ]"
      v-model="lang"
    />
  </q-page>
</template>

<style>
</style>

<script>
export default {
  name: 'PageIndex'
}
</script>
