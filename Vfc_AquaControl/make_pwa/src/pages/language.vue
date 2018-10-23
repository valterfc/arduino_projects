<template>
  <q-page class="flex flex-center">
    <q-select
      stack-label="Select Your Language"
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
  data () {
    return {
      lang: this.$q.i18n.lang
    }
  },
  watch: {
    lang (lang) {
      // dynamic import, so loading on demand only
      import(`quasar-framework/i18n/${lang}`).then(lang => {
        this.$q.i18n.set(lang.default)
      })
    }
  },
  name: 'PageIndex'
}
</script>
