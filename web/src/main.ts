import { EMPTY_BOARD, playerMove, statusText } from "./game.ts";

const cells = [...document.querySelectorAll<HTMLButtonElement>(".cell")];
const status = document.getElementById("status")!;
let board = EMPTY_BOARD;
let over = false;

function render(winner: string): void {
  cells.forEach((c, i) => (c.textContent = board[i] === "." ? "" : board[i]));
  status.textContent = statusText(winner);
  over = winner !== ".";
}

cells.forEach((cell, i) =>
  cell.addEventListener("click", async () => {
    const next = over ? null : playerMove(board, i);
    if (!next) return;
    board = next;
    render(".");
    const res = await fetch("/api/move", {
      method: "POST",
      body: JSON.stringify({ board }),
    });
    const data: { board: string; winner: string } = await res.json();
    board = data.board;
    render(data.winner);
  }),
);

document.getElementById("reset")!.addEventListener("click", () => {
  board = EMPTY_BOARD;
  render(".");
});
