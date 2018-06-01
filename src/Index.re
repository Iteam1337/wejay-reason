Css.(global("*", [boxSizing(borderBox)]));

Css.(
  global(
    "body, html",
    [
      backgroundColor(hex("fff")),
      color(hex(Theme.colors.foreground)),
      fontFamily("'Roboto', Helvetica, sans-serif"),
      margin(px(0)),
      padding(px(0)),
    ],
  )
);

ReactDOMRe.renderToElementWithId(
  <ReasonApollo.Provider client=Client.instance>
    <App />
  </ReasonApollo.Provider>,
  "root",
);
