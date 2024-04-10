#include "house.h"

/* Updates the graphics for the window @ coordinates (x, y) to match the
 * `state` array.
 *
 *   This function modifies the `house` array by updating the characters
 *   inside the window located at the zero indexed coordinates (x, y) to
 *   match the window's state in the `state` array.  If the window's
 *   state is 1, then the window is filled with the '#' character.
 *   Likewise, if the window's state is 0 in the `state` array, the
 *   window is filled with the ' ' character.
 *
 * Parameters:
 *   house -- pointer to characters representing the house
 *
 *   state -- pointer to the game state array
 *
 *       x -- the horizontal coordinate of the window for which the
 *            state will be updated (zero indexed, with 0 being
 *            the left column and 2 being the right column)
 *
 *       y -- the vertical coordinate of the window for which the
 *            state will be updated (zero indexed, with 0 being
 *            the top row and 2 being the bottom row)
 */
void window_update_graphics (char *house, const int *state, int x, int y)
{
  /* Step 1: Write this function! */
  int row_0, col_0;
  
  row_0 = 8+6*y; col_0 = 11+18*x;
  int temp;
  temp = y*3+x;
  int i, j;
  for (i = row_0;i < row_0+WINDOW_HEIGHT; i++){
    for (j = col_0; j < col_0 + WINDOW_WIDTH; j++){
      if (state[temp] == 0){
        house[i * HOUSE_WIDTH+j] = ' ';
      }
      else{
        house[i * HOUSE_WIDTH + j] = '#';
      }
  }


  }

  }



/* Toggles the state of the window @ coordinates (x, y) in the game
 * state array.
 *
 *   This function modifies the `state` array by toggling the value
 *   corresponding to the window at the provided coordinates (x, y).  If
 *   the current value is 1, then it will be toggled to 0.  Likewise, if
 *   the current value is 0, then it will be toggled to 1.
 *
 * Parameters:
 *   state -- pointer to the game state array
 *
 *       x -- the horizontal coordinate of the window for which the
 *            state will be updated (zero indexed, with 0 being
 *            the left column and 2 being the right column)
 *
 *       y -- the vertical coordinate of the window for which the
 *            state will be updated (zero indexed, with 0 being
 *            the top row and 2 being the bottom row)
 */
void window_toggle_state (int *state, int x, int y)
{
  int index = y * 3 + x;
  switch(state[index]){
    case 0:
    state[index] = 1;
    break;
    default:
    state[index] = 0;
    break;
  }
}


/* Toggles the state and, correspondingly, updates the graphics for the
 * window @ coordinates (x, y).
 *
 *   Given the zero indexed coordinates (x, y) of a window, this
 *   function ensures that the corresponding element in the game state
 *   array is toggled appropriately and that the graphics corresponding
 *   to that window are updated appropriately to reflect the new state.
 *
 *   Hint: call other functions you have written to make this easier.
 *
 * Parameters:
 *   state -- pointer to the game state array
 *
 *   house -- pointer to characters representing the house
 *
 *       x -- the horizontal coordinate of the window for which the
 *            state will be updated (zero indexed, with 0 being
 *            the left column and 2 being the right column)
 *
 *       y -- the vertical coordinate of the window for which the
 *            state will be updated (zero indexed, with 0 being
 *            the top row and 2 being the bottom row)
 */
void window_update (int *state, char *house, int x, int y)
{
  /* Step 2: Write this function! */
  window_toggle_state(state,x,y);
  window_update_graphics(house,state,x,y);
}


/* Toggles the lights based on the user's window selection.
 *
 *   Given the user's choice of window number, this function updates the
 *   corresponding window's (or windows') state and graphics, as
 *   necessary.
 *
 *   Hints:
 *     -- A primary job of this function will be to convert the choice
 *        of the user into the zero indexed (x, y) coordinates of a
 *        window.
 *
 *     -- Converting between `choice` and the (x, y) coordinates will
 *        probably be easier if you internally number the windows
 *        starting at zero (i.e. 0 thru 8 instead of 1 thru 9).
 *
 *     -- This function will need to call one other function
 *        (perhaps multiple times).
 *
 *   For Step 2, this function will only toggle the window
 *   corresponding to the user's selection.
 *
 *   For Step 3, this function will toggle the selected window
 *   and its neighbors (as described above in the instructions).
 *
 * Parameters:
 *    state -- pointer to the game state array
 *
 *    house -- pointer to characters representing the house
 *
 *   choice -- integer corresponding to the user's window selection
 *             (an integer value within the range 1 to 9)
 */
void window_toggle (int *state, char *house, int choice)
{
  /* Step 2: Write this function! (for single window toggle) */
choice -= 1;
int x = choice % 3; int y = choice / 3; 
window_update(state, house, x, y);
  /* Step 3: Rewrite this function! (for multi-window toggle) */
/* these conditionals modify nearby windows/elements */
  if (x != 0){
    window_update(state, house, x-1,y);
  }
  if (x != 2){
    window_update(state, house, x+1,y);
  }
  if (choice > 2){
    window_update(state, house, x,y-1);
  }
  if(choice < 6){
    window_update(state,house,x,y+1);
  }
}