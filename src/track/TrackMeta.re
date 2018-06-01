open Css;

let component = ReasonReact.statelessComponent("TrackMeta");

let trackName =
  style([
    color(rgba(54, 61, 67, 1.0)),
    fontSize(px(14)),
    fontWeight(500),
  ]);

let trackMeta = style([lineHeight(1.4)]);

let make = (~className=trackName, ~track, _children) => {
  ...component,
  render: _self =>
    <div className=trackMeta>
      <div className=className> (track##name |> Utils.ste) </div>
      <Artists track />
    </div>,
};
