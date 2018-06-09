let component = ReasonReact.statelessComponent("Input");

module Styles = {
  open Css;

  let label = style([display(`block), marginBottom(px(10))]);

  let input =
    style([
      border(px(1), `solid, hex(Theme.colors.border)),
      borderRadius(px(3)),
      display(`block),
      padding(px(10)),
      width(pct(100.0)),
    ]);
};

let make =
    (~type_="text", ~helpText=?, ~id, ~label, ~onChange, ~value, _children) => {
  ...component,
  render: _self =>
    <div className="field">
      <div className="control">
        <label className=Styles.label htmlFor=id> (label |> Utils.ste) </label>
        <input
          type_
          className=Styles.input
          id
          onChange=(ReForm.Helpers.handleDomFormChange(onChange))
          value
        />
      </div>
      (
        switch (helpText) {
        | Some(text) =>
          <p className="help has-text-left"> (text |> Utils.ste) </p>
        | None => ReasonReact.null
        }
      )
    </div>,
};
