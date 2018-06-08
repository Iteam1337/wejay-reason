let component = ReasonReact.statelessComponent("Input");

module Styles = {
  open Css;

  let input =
    style([
      background(none),
      borderBottom(px(1), solid, hex("fff")),
      border(px(0), none, transparent),
      color(hex("fff")),
      fontSize(px(20)),
      paddingBottom(px(10)),
      transition(~duration=200, ~timingFunction=easeInOut, "border-color"),
      width(pct(100.0)),
      selector(
        ":focus",
        [
          borderColor(hex(Theme.colors.wejay)),
          outline(px(0), none, transparent),
        ],
      ),
    ]);
};

let make = (~type_="text", ~onChange, ~value, _children) => {
  ...component,
  render: _self =>
    <input
      type_
      className=Styles.input
      id="email"
      onChange=(ReForm.Helpers.handleDomFormChange(onChange))
      placeholder="Search"
      value
    />,
};
