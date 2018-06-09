let component = ReasonReact.statelessComponent("Button");

module Styles = {
  open Css;

  let button =
    style([
      backgroundColor(`transparent),
      border(px(1), `solid, hex(Theme.colors.wejay)),
      borderRadius(px(4)),
      cursor(`pointer),
      fontSize(px(16)),
      padding(px(10)),
      transitions([
        transition(
          ~duration=150,
          ~timingFunction=easeInOut,
          "background-color",
        ),
        transition(~duration=150, ~timingFunction=easeInOut, "color"),
      ]),
      selector(
        ":hover",
        [backgroundColor(hex(Theme.colors.wejay)), color(hex("fff"))],
      ),
    ]);
};

let make = (~type_="button", children) => {
  ...component,
  render: _self => <button type_ className=Styles.button> children </button>,
};
