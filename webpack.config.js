const path = require('path')
const HtmlWebPackPlugin = require('html-webpack-plugin')
const history = require('connect-history-api-fallback')
const convert = require('koa-connect')
const isProd = process.env.NODE_ENV === 'production'

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
