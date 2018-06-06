# wejay-reason

## Run Project

```sh
npm install
npm start
# in another tab
npm run webpack
```

Open up the url specified in the webpack tab (webpack-serve).

## Build for Production

```sh
npm run build
npm run webpack:production
```

This will replace the development artifact `build/Index.js` for an optimized version.

**To enable dead code elimination**, change `bsconfig.json`'s `package-specs` `module` from `"commonjs"` to `"es6"`. Then re-run the above 2 commands. This will allow Webpack to remove unused code.
