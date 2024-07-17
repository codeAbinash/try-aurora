/** @type {import('tailwindcss').Config} */
export default {
  content: ['./index.html', './src/**/*.{js,ts,jsx,tsx}', 'node_modules/codeabinash-test-button/dist/index.js'],
  theme: {
    extend: {},
  },
  plugins: [require('@tailwindcss/typography')],
}
