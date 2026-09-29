import assert from "node:assert/strict";
import { test } from "node:test";
import { EMPTY_BOARD, playerMove, statusText } from "../web/src/game.ts";

test("playerMove places X on empty cell only", () => {
  assert.equal(playerMove(EMPTY_BOARD, 4), "....X....");
  assert.equal(playerMove("....X....", 4), null);
  assert.equal(playerMove(EMPTY_BOARD, 9), null);
});

test("statusText", () => {
  assert.equal(statusText("D"), "Draw.");
  assert.equal(statusText("."), "Your move (X).");
});
