open Css;

let component = ReasonReact.statelessComponent("TrackDuration");

let trackDuration =
  style([color(rgba(54, 61, 67, 0.8)), fontSize(px(12))]);

let make = (~track, _children) => {
  ...component,
  render: _self =>
    <div className=trackDuration>
      (track##duration |> float_of_int |> Duration.parse |> Utils.ste)
    </div>,
};
