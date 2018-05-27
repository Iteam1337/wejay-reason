open Css;

let component = ReasonReact.statelessComponent("Artists");

let artists = style([]);

let make = (~track, _children) => {
  ...component,
  render: _self =>
    <div className=artists>
      (
        Js.Array.map(artist => artist##name, track##artists)
        |> Js.Array.joinWith(", ")
        |> Utils.ste
      )
    </div>,
};
