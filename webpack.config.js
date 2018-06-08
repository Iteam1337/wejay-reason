const path = require('path')
const HtmlWebPackPlugin = require('html-webpack-plugin')
const history = require('connect-history-api-fallback')
const convert = require('koa-connect')
const isProd = process.env.NODE_ENV === 'production'
const webpack = require('webpack')

require('dotenv').config()

module.exports = {
  entry: './lib/js/src/Index.bs.js',
  mode: isProd ? 'production' : 'development',
  output: {
    path: path.join(__dirname, 'build/'),
    publicPath: '/',
    filename: '[name].[hash:8].js'
  },

  plugins: [
    new HtmlWebPackPlugin({
      inject: true,
      template: './src/index.html'
    }),
    new webpack.DefinePlugin({
      REACT_APP_GRAPHQL_URL: JSON.stringify(process.env.REACT_APP_GRAPHQL_URL)
    })
  ],

  serve: {
    add: app => {
      app.use(convert(history()))
    },
    dev: {
      stats: 'minimal',
      publicPath: '/'
    },
    hot: {
      hot: true
    },
    port: 3000
  }
}
