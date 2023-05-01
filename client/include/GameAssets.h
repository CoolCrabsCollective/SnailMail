//
// Created by Alexander Winter on 2022-02-13.
//

#ifndef GAMETEMPLATE_GAMEASSETS_H
#define GAMETEMPLATE_GAMEASSETS_H

#include "WIZ/asset/MusicAsset.h"
#include "WIZ/asset/SoundAsset.h"
#include "WIZ/asset/FontAsset.h"
#include "WIZ/asset/TextureAsset.h"

#ifndef ASSET
#define ASSET(TYPE, NAME, CONSTRUCTOR) extern const TYPE NAME;
#endif

namespace GameAssets {
	extern std::vector<const wiz::AssetBase*> ALL;

	ASSET(wiz::MusicAsset, SNAILYS_SONG, ("music/snailys_song_v1.mp3"))
    ASSET(wiz::MusicAsset, SNAIL_FRIENDS_60, ("music/Snail_Friends_60_bpm.ogg"))
    ASSET(wiz::MusicAsset, SNAIL_FRIENDS_70, ("music/Snail_Friends_70_bpm.ogg"))
    ASSET(wiz::MusicAsset, SNAIL_FRIENDS_80, ("music/Snail_Friends_80_bpm.ogg"))
    ASSET(wiz::MusicAsset, SNAIL_FRIENDS_90, ("music/Snail_Friends_90_bpm.ogg"))
    ASSET(wiz::MusicAsset, SNAIL_FRIENDS_100, ("music/Snail_Friends_100_bpm.ogg"))
    ASSET(wiz::MusicAsset, SNAIL_FRIENDS_110, ("music/Snail_Friends_110_bpm.ogg"))
    ASSET(wiz::MusicAsset, SNAIL_FRIENDS_120, ("music/Snail_Friends_120_bpm.ogg"))
    ASSET(wiz::MusicAsset, SNAIL_FRIENDS_130, ("music/Snail_Friends_130_bpm.ogg"))
    ASSET(wiz::MusicAsset, SNAIL_FRIENDS_140, ("music/Snail_Friends_140_bpm.ogg"))
    ASSET(wiz::MusicAsset, SNAIL_FRIENDS_150, ("music/Snail_Friends_150_bpm.ogg"))
	ASSET(wiz::SoundAsset, JUMP, ("sfx/jump.ogg"))
	ASSET(wiz::FontAsset, THE_RIGHT_FONT, ("font/VT323-Regular.ttf"))

	ASSET(wiz::TextureAsset, WHITE_PIXEL, ("gfx/white_pixel.png"))
    ASSET(wiz::TextureAsset, PATH, ("gfx/path.png"))
    ASSET(wiz::TextureAsset, CUM_PATH, ("gfx/cum_path.png"))
    ASSET(wiz::TextureAsset, GRAPH_VERTEX, ("gfx/graph_vertex.png"))
    ASSET(wiz::TextureAsset, SNAILY, ("gfx/snaily.png"))
    ASSET(wiz::TextureAsset, SNAILY_CAP, ("gfx/snaily_cap.png"))
    ASSET(wiz::TextureAsset, POST_OFFICE, ("gfx/post_office.png"))

    ASSET(wiz::TextureAsset, GRASS_0, ("gfx/grass/grass_0.png"))
    ASSET(wiz::TextureAsset, GRASS_1, ("gfx/grass/grass_1.png"))
    ASSET(wiz::TextureAsset, GRASS_2, ("gfx/grass/grass_2.png"))

    ASSET(wiz::TextureAsset, FLOWER_0, ("gfx/grass/flower_0.png"))
    ASSET(wiz::TextureAsset, FLOWER_1, ("gfx/grass/flower_1.png"))

    ASSET(wiz::TextureAsset, YELLOW_FLOWER_0, ("gfx/grass/yellow_flower_0.png"))
    ASSET(wiz::TextureAsset, YELLOW_FLOWER_1, ("gfx/grass/yellow_flower_1.png"))

    ASSET(wiz::TextureAsset, BLUE_FLOWER_0, ("gfx/grass/blue_flower_0.png"))
    ASSET(wiz::TextureAsset, BLUE_FLOWER_1, ("gfx/grass/blue_flower_1.png"))

    // TITLE SCREEN
    ASSET(wiz::TextureAsset, TITLE_SCREEN_BACKGROUND, ("gfx/cover_art.png"))

    // FRIENDS (KAWAII ONLY)
    ASSET(wiz::TextureAsset, BEE, ("gfx/thicc_bee.png"))
    ASSET(wiz::TextureAsset, BEE_SPRITE_SHEET, ("gfx/bee_sprite_sheet.png"))
    ASSET(wiz::TextureAsset, LADY_BUG, ("gfx/kawaii_ladybug.png"))
    ASSET(wiz::TextureAsset, LADY_BUG_SPRITE_SHEET, ("gfx/ladybug_sprite_sheet.png"))
    ASSET(wiz::TextureAsset, MOUSE, ("gfx/kawaii_mouse.png"))
    ASSET(wiz::TextureAsset, MOUSE_SPRITE_SHEET, ("gfx/mouse_sprite_sheet.png"))
    ASSET(wiz::TextureAsset, FROG, ("gfx/kawaii_frog.png"))
    ASSET(wiz::TextureAsset, FROG_SPRITE_SHEET, ("gfx/frog_sprite_sheet.png"))

    // UI
    ASSET(wiz::TextureAsset, PATH_SEL_ARROW, ("gfx/ui/path_select_arrow.png"))
    ASSET(wiz::TextureAsset, CHAT_BUBBLE, ("gfx/ui/chat_bubble.png"))
    ASSET(wiz::TextureAsset, CHAT_BUBBLE_MAD, ("gfx/ui/chat_bubble_mad.png"))
    ASSET(wiz::TextureAsset, BEE_LETTER, ("gfx/ui/letters/bee_icon.png"))
    ASSET(wiz::TextureAsset, FROG_LETTER, ("gfx/ui/letters/frog_icon.png"))
    ASSET(wiz::TextureAsset, LADY_BUG_LETTER, ("gfx/ui/letters/lady_bug_icon.png"))
    ASSET(wiz::TextureAsset, MOUSE_LETTER, ("gfx/ui/letters/mouse_icon.png"))
    ASSET(wiz::TextureAsset, BUTTON, ("gfx/ui/button.png"))
    ASSET(wiz::TextureAsset, ALEXS_DESIRE, ("gfx/ui/alexs_desire.png"))
    ASSET(wiz::TextureAsset, LEVEL_INDICATOR, ("gfx/ui/level_sel/level_indicator.png"))
    ASSET(wiz::TextureAsset, LEVEL_SEL_MENU_BACKDROP, ("gfx/ui/level_sel/level_sel_menu_backdrop.png"))
    ASSET(wiz::TextureAsset, LEVEL_SEL_MENU_EXIT, ("gfx/ui/level_sel/level_sel_menu_exit.png"))
    ASSET(wiz::TextureAsset, LEVEL_SEL_MENU_ITEM, ("gfx/ui/level_sel/level_sel_menu_item_backdrop.png"))

    // SHELLS
    ASSET(wiz::TextureAsset, BRONZE_SHELL, ("gfx/ui/shells/bronze.png"))
    ASSET(wiz::TextureAsset, SILVER_SHELL, ("gfx/ui/shells/silver.png"))
    ASSET(wiz::TextureAsset, GOLD_SHELL, ("gfx/ui/shells/gold.png"))
    ASSET(wiz::TextureAsset, LOSER_SHELL, ("gfx/ui/shells/loser.png"))
}


#endif //GAMETEMPLATE_GAMEASSETS_H
