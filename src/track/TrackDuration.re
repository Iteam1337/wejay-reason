open Css;

[@bs.val] [@bs.module "track-duration"] external parse : int => string = "";

let component = ReasonReact.statelessComponent("TrackDuration");

let trackDuration =
  style([
    color(rgba(54, 61, 67, 0.6)),
    fontSize(px(12)),
    fontWeight(500),
    textAlign(`right),
  ]);

let make = (~track, _children) => {
  ...component,
  render: _self =>
    <div className=trackDuration>
      (parse(int_of_float(track##duration)) |> Utils.ste)
    </div>,
};
