let component = ReasonReact.statelessComponent("Menu");

module Styles = {
  open Css;

  let menu =
    style([
      alignItems(center),
      backgroundColor(hex(Theme.colors.foreground)),
      display(`flex),
      flexDirection(column),
    ]);

  let logo =
    style([
      backgroundColor(hex(Theme.colors.wejay)),
      height(px(50)),
      marginBottom(px(20)),
      width(px(50)),
    ]);
};

let make = _children => {
  ...component,
  render: _self =>
    <div className=Styles.menu>
      <div className=Styles.logo />
      <Search />
    </div>,
};
