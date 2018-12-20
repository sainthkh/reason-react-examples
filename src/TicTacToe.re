
let component = ReasonReact.statelessComponent("TicTacToe")

let make = (_children) => {
    ...component,
    render: (_self) => {
        <div>
            <h1>{ReasonReact.string("Tic Tac Toe")}</h1>
            <Board />
        </div>
    }
}