// Pure game logic, no DOM, so node can test it directly.

export type Board = string;

export const EMPTY_BOARD: Board = ".........";

/** Human plays X. Returns new board, or null if the move is illegal. */
export function playerMove(board: Board, cell: number): Board | null {
  if (cell < 0 || cell > 8 || board[cell] !== ".") return null;
  return board.slice(0, cell) + "X" + board.slice(cell + 1);
}

/** Status line for the engine's winner code. */
export function statusText(winner: string): string {
  switch (winner) {
    case "X":
      return "You win!";
    case "O":
      return "Engine wins.";
    case "D":
      return "Draw.";
    default:
      return "Your move (X).";
  }
}
