open Css;

let component = ReasonReact.statelessComponent("Artists");

let artistItem =
  style([
    color(hex("363d43")),
    textDecoration(none),
    selector(":hover", [textDecoration(underline)]),
  ]);

let make = (~track, _children) => {
  ...component,
  render: _self =>
    <div>
      (
        Js.Array.mapi(
          (artist, i) =>
            [|
              <a className=artistItem href=artist##uri>
                (artist##name |> Utils.ste)
              </a>,
              i < Js.Array.length(track##artists) - 1 ?
                <span> (", " |> Utils.ste) </span> : ReasonReact.null,
            |]
            |> ReasonReact.array,
          track##artists,
        )
        |> ReasonReact.array
      )
    </div>,
};
