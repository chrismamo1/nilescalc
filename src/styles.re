let displayFlex =
  ReactDOMRe.Style.make(~display="flex", ());

let mkFlex(x) =
  ReactDOMRe.Style.make(~flex=x, ());

let combine = ReactDOMRe.Style.combine;

let combineN(styles) =
  switch (styles) {
  | [hd, ...tl] =>
    List.fold_left(ReactDOMRe.Style.combine, hd, tl)
  | _ =>
    ReactDOMRe.Style.make()
  }