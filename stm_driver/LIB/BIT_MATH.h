

#ifndef BIT_MATH_H
#define BIT_MATH_H

/**
 * [SET_BIT: set one bit in register]
 * @param  REG               [register]
 * @param  BIT               [the position of the bit]
 * @return     [no return]
 */
#define SET_BIT(REG,BIT) (REG |= ((0x01)<<(BIT)))

/**
 * [CLR_BIT: clear one bit in register]
 * @param  REG               [register]
 * @param  BIT               [the position of the bit]
 * @return     [no return]
 */

#define CLR_BIT(REG,BIT) (REG &= ~((0x01)<<(BIT)))
/**
 * [TGL_BIT: toggle one bit in register]
 * @param  REG               [register]
 * @param  BIT               [the position of the bit]
 * @return     [no return]
 */

#define TGL_BIT(REG,BIT) (REG ^= ((0x01)<<(BIT)))

/**
 * [GET_BIT get one bit value]
 * @param  REG               [register]
 * @param  BIT               [the position of the bit]
 * @return     [the value of the bit 0 or 1]
 */
#define GET_BIT(REG,BIT) (((REG)>>(BIT)) & (0x01))


#endif
