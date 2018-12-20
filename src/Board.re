type player = [`O | `X];
type boardValue = [player | `Empty];

let changePlayer = (player) => 
    switch(player) {
    | `O => `X
    | `X => `O
    }

let string_of_player = player => 
    switch(player) {
    | `O => "O"
    | `X => "X"
    }

let boardValue_of_player = player => 
    switch(player) {
    | `O => `O
    | `X => `X
    }

let string_of_boardValue = boardValue => 
    switch(boardValue) {
    | `O => "O"
    | `X => "X"
    | `Empty => ""
    }

type state = {
    turn: player,
    board: array(boardValue),
    winner: boardValue,
};

let findWinner = (board: array(boardValue)) => {
    let lines = [|
        (0, 1, 2),
        (3, 4, 5),
        (6, 7, 8),
        (0, 3, 6),
        (1, 4, 7),
        (2, 5, 8),
        (0, 4, 8),
        (2, 4, 6),
    |];

    let winner = ref(`Empty);
    let i = ref(0);

    while(winner^ == `Empty && i^ < 8) {
        let (a, b, c) = lines[i^];
        if(board[a] == board[b] && board[b] == board[c] && board[c] == board[a]) {
            winner := board[a]
        }
        i := i^ + 1;
    }

    winner^
}

type action = FinishTurn(player, int);

let component = ReasonReact.reducerComponent("Board");

let make = (_children) => {
    ...component,
    initialState: () => {
        turn: `X,
        board: [|
            `Empty, `Empty, `Empty,
            `Empty, `Empty, `Empty,
            `Empty, `Empty, `Empty,
            |],
        winner: `Empty,
    },

    reducer: (action, state) => {
        switch(action) {
        | FinishTurn(player, pos) => {
            switch(state.board[pos]) {
            | `Empty => {
                state.board[pos] = boardValue_of_player(player);
                ReasonReact.Update({...state, turn: changePlayer(player), winner: findWinner(state.board)})
            }
            | _ => ReasonReact.NoUpdate
            }            
        }
        }
    },

    render: self => {
        let onClick = pos => _event => {
            self.send(FinishTurn(self.state.turn, pos))
        };

        let square = (index) => 
            <Square value=self.state.board[index] onClick=onClick(index) />;
        
        <div>
            <div>
            {
                switch(self.state.winner) {
                | `Empty => ReasonReact.string("Current Player: " ++ string_of_player(self.state.turn))
                | _ => ReasonReact.string("Winner: " ++ string_of_boardValue(self.state.winner))
                }
            }
            </div>
            <div className="board-row">
                {square(0)}
                {square(1)}
                {square(2)}
            </div>
            <div className="board-row">
                {square(3)}
                {square(4)}
                {square(5)}
            </div>
            <div className="board-row">
                {square(6)}
                {square(7)}
                {square(8)}
            </div>
        </div>
    }
}