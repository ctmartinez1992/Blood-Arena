#ifndef RL_WEAPON_FACTORY_HPP
#define RL_WEAPON_FACTORY_HPP

//TODO: 
//global_variable char WEAPON_SWORD_STOCK_NAME = 'o';

Weapon*
CreateWeaponRandom();

//1H Swords
Weapon*
CreateWeaponSword1HWood();

Weapon*
CreateWeaponSword1HStone();

Weapon*
CreateWeaponSword1HIron();

Weapon*
CreateWeaponSword1HLegendary();

//Shields
Weapon*
CreateWeaponShieldWood();

Weapon*
CreateWeaponShieldStone();

Weapon*
CreateWeaponShieldIron();

#endif