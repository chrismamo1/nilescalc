type state = {
  stack: list(int)
};

type action =
  | Push(int)
  | Add
  | Multiply
  | Subtract
  | Divide;

let component = ReasonReact.reducerComponent("Calculator");

let make = (_children) => {
  ...component,
  initialState: () => {stack: []},
  reducer: (action, state) =>
    switch (action) {
    | Add | Multiply | Divide | Subtract =>
      switch (state.stack) {
      | [op2, op1, ...rest] =>
        let op =
          switch (action) {
          | Add => ( + )
          | Multiply => ( * )
          | Divide => ( / )
          | Subtract => ( - )
          };
        let res = op(op1, op2)
        let stack = [res, ...rest];
        ReasonReact.Update({stack: stack})
      | _ =>
        ReasonReact.NoUpdate
      }
    | Push(num) =>
      ReasonReact.Update({stack: [num, ...state.stack]})
    },

  render: self => {
    let stack = {
      let mkRow(num) = {
        <div>
          {ReasonReact.string(string_of_int(num))}
        </div>
      };
      let stack =
        List.map(mkRow, self.state.stack)
        |> Array.of_list;
      <div style={ReactDOMRe.Style.make(~width="100px", ())}>
        {ReasonReact.array(stack)}
      </div>
    };
    <div style={ReactDOMRe.Style.make(~display="flex", ())}>
      <div style={ReactDOMRe.Style.make(~flex="1", ())}>
        <NumPad submit={num => self.send(Push(num))} />
      </div>
      <div style={ReactDOMRe.Style.make(~flex="1", ())}>
        <button onClick={_event => self.send(Add)}>
          {ReasonReact.string("+")}
        </button>
        <button onClick={_event => self.send(Multiply)}>
          {ReasonReact.string("*")}
        </button>
        <button onClick={_event => self.send(Subtract)}>
          {ReasonReact.string("-")}
        </button>
        <button onClick={_event => self.send(Divide)}>
          {ReasonReact.string("/")}
        </button>
      </div>
      stack
    </div>;
  },
};
