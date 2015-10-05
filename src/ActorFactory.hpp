#ifndef RL_ACTOR_FACTORY_HPP
#define RL_ACTOR_FACTORY_HPP

//80
global_variable char namePrefix[][6] = {
	"ak", "am", "ash", "az", "bag", "bar", "blo", "bor", "bro", "bub",
	"bu", "dug", "dush", "fel", "flak", "ful", "gham", "ghu", "gim", "gluk",
	"golm", "gor", "grub", "gund", "hor", "hosh", "hu", "hum", "ish", "ka",
	"koth", "kru", "kug", "lat", "lorm", "lug", "ma", "mal", "mogg", "mor",
	"moz", "mugg", "muz", "nak", "naz", "nor", "ol", "or", "orth", "oth",
	"pig", "prak", "pug", "push", "rat", "ronk", "rug", "ruk", "sha", "sku",
	"sna", "tak", "tar", "thak", "thra", "thu", "torz", "tu", "tug", "tum",
	"ugg", "uk", "ush", "uth", "zaa", "zog", "zor", "zug", "zun", "zur"
};

//80
global_variable char nameSuffix[][6] = {
	"arz", "ash", "bag", "bak", "blik", "bug", "buk", "dash", "dug", "dush",
	"dza", "fa", "fel", "flak", "garn", "ggu", "gha", "glob", "gog", "gol",
	"gor", "goth", "grat", "grish", "gug", "gum", "ham", "hog", "hom", "hork",
	"hug", "imp", "ka", "kra", "krak", "krimp", "kug", "lorg", "lorm", "lug",
	"luga", "luk", "maku", "mog", "mogg", "moz", "mub", "mug", "nak", "ogg",
	"ol", "olm", "org", "orgu", "oth", "prak", "rish", "rok", "rom", "ronk",
	"rsko", "rug", "ruk", "shak", "shu", "skak", "sko", "skun", "thog", "thra",
	"thrak", "thug", "ug", "uk", "unn", "ura", "uth", "zog", "zu", "zub"
};

//83
global_variable char nicknames[][17] = {
	"Ash-Skin", "Coal-Skin", "Green-skin",
	"Bag-Head", "Barrel-Head", "Pot-Head",
	"Black-Blade", "Rusty-Blade", "Shiny-Blade",
	"Metal-Beard", "Metal-Eye", "Metal-Leg",
	"Iron Jaws", "Bone Jaws", "Jaws",
	"No Tongue", "No Ears", "No Nose", "No Teeth", "No Hair",
	"Skull-Cracker", "Skull-Licker", "Skull-Sniffer",
	"The Bald", "The Blind", "The Mute", "The Deaf", "The Voice",
	"The Advisor", "The Amputator", "The Assassin", "The Beheader", "The Bitter",
	"The Black", "The Bloated", "The Brave", "The Brown", "The Choker",
	"The Clever", "The Corrupt", "The Coward", "The Crazy", "The Defiler",
	"The Devourer", "The Diseased", "The Drunk", "The Fool", "The Friendly",
	"The Gentle", "The Hacker", "The Handsome", "The Humiliator", "The Hungry",
	"The Legend", "The Loaded", "The Mad", "The Meat Hoarder", "The Merciful",
	"The Mountain", "The Proud", "The Puny", "The Rash", "The Red",
	"The Savage", "The Screamer", "The Serpent", "The Shadow", "The Shield",
	"The Slasher", "The Small", "The Smasher", "The Spike", "The Stout",
	"The Surgeon", "The Swift", "The Twister", "The Vile", "The Wise",
	"The Drooler", "The Spitter", "The Puker", "The Shitter", "The Pisser"
};

global_variable char ORC_THUG_CODE = 'o';
global_variable TCODColor ORC_THUG_COLOR = TCODColor::lightGreen;

global_variable char ORC_FIGHTER_CODE = 'o';
global_variable TCODColor ORC_FIGHTER_COLOR = TCODColor::darkGreen;

global_variable char ORC_VETERAN_CODE = 'o';
global_variable TCODColor ORC_VETERAN_COLOR = TCODColor::darkestGreen;

global_variable char ITEM_POTION_HEALTH_CODE = '!';
global_variable TCODColor ITEM_POTION_HEALTH_COLOR = TCODColor::violet;

global_variable char ITEM_SCROLL_LIGHTNING_BOLT_CODE = '#';
global_variable TCODColor ITEM_SCROLL_LIGHTNING_BOLT_COLOR = TCODColor::lightBlue;

global_variable char ITEM_SCROLL_FIREBALL_CODE = '#';
global_variable TCODColor ITEM_SCROLL_FIREBALL_COLOR = TCODColor::lightOrange;

global_variable char ITEM_SCROLL_CONFUSION_CODE = '#';
global_variable TCODColor ITEM_SCROLL_CONFUSION_COLOR = TCODColor::lightGrey;

//PLayer
Actor*
CreateActorPlayer();

//Orcs
Actor*
CreateActorFullRandomOrc();

Actor*
CreateActorOrcThug(int x, int y);

Actor*
CreateActorOrcFighter(int x, int y);

Actor*
CreateActorOrcVeteran(int x, int y);

//Items
Actor*
CreateActorItemPotionHealth(int x, int y);

Actor*
CreateActorItemScrollLightningBolt(int x, int y);

Actor*
CreateActorItemScrollFireball(int x, int y);

#endif