type state = {
  num: int,
};

type action =
  | Digit(int)
  | Back
  | Submit;

let component = ReasonReact.reducerComponent("NumPad");

let make = (~submit, _children) => {
  ...component,
  initialState: () => { num: 0 },
  reducer: (action, state) =>
    switch (action) {
    | Digit(digit) =>
      ReasonReact.Update({num: state.num * 10 + digit})
    | Back =>
      ReasonReact.Update({num: state.num / 10})
    | Submit =>
      let num = state.num;
      ReasonReact.UpdateWithSideEffects({num: 0}, self => submit(num))
    },
  render: self => {
    let buttonStyle =
      ReactDOMRe.Style.make(~padding="5px", ())
      |> Styles.combine(Styles.mkFlex("1"));
    let buttons =
      [|  [|7,8,9|]
      ,   [|4,5,6|]
      ,   [|1,2,3|]
      ,   [|0|]
      |]
      |>  Array.map(
            row => {
              let buttons =
                Array.map(
                  num =>
                    <button
                      style={buttonStyle}
                      onClick={_event => self.send(Digit(num))}
                    >
                      {ReasonReact.string(string_of_int(num))}
                    </button>,
                  row
                );
              <div style={ReactDOMRe.Style.make(~display="flex", ~flexDirection="row", ())}>
                {ReasonReact.array(buttons)}
              </div>
            }
          );
    <div>
      <div>
        {ReasonReact.string(string_of_int(self.state.num))}
      </div>
      <div>
        {ReasonReact.array(buttons)}
      </div>
      <div style={Styles.displayFlex}>
        <button style={buttonStyle} onClick={_event => self.send(Submit)}>
          {ReasonReact.string("Enter")}
        </button>
        <button style={buttonStyle} onClick={_event => self.send(Back)}>
          {ReasonReact.string("Back")}
        </button>
      </div>
    </div>
  }
};