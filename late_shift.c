// Late Shift gamecode reimplementation
#include <stdio.h>
#include <ctype.h>
#include <vitasdk.h>
#include <vitaGL.h>
#include "audio.h"
#include "draw.h"
#include "engine.h"
#include "player.h"
#include "late_shift.h"

#ifdef LATE_SHIFT
char game_strings[NUM_GAME_STRINGS][128];

// Prototypes
sequence *seg951_1_951_2();

// Game get text funcs
char *selfless() { return game_strings[31]; }
char *selfish() { return game_strings[32]; }
char *board() { return game_strings[33]; }
char *help() { return game_strings[34]; }
char *yes() { return game_strings[36]; }
char *no() { return game_strings[37]; }
char *why() { return game_strings[38]; }
char *why_at_all() { return game_strings[47]; }
char *okay() { return game_strings[43]; }
char *not_good_enough() { return game_strings[44]; }
char *ok() { return game_strings[48]; }
char *two_hundred() { return game_strings[49]; }
char *forget_it() { return game_strings[50]; }
char *deal() { return game_strings[51]; }
char *three_hundred() { return game_strings[52]; }
char *ignore() { return game_strings[55]; }
char *nevermind() { return game_strings[62]; }
char *check_cctv() { return game_strings[63]; }
char *call_police() { return game_strings[64]; }
char *go_there() { return game_strings[65]; }
char *take_pepper_spray() { return game_strings[66]; }
char *text_has_pepper() { return game_vars.has_pepper_spray ? game_strings[71] : no(); }
char *go_check() { return game_strings[41]; }
char *all_clear() { return game_strings[60]; }
char *keep_pepper_spray() { return game_strings[67]; }
char *drop_it() { return game_strings[68]; }
char *drive() { return game_strings[74]; }
char *run() { return game_strings[75]; }
char *turn_back() { return game_strings[76]; }
char *keep_going() { return game_strings[77]; }
char *do_it() { return game_strings[80]; }
char *go() { return game_strings[85]; }
char *no_go() { return game_strings[86]; }
char *leg_it() { return game_strings[84]; }
char *contradict() { return game_strings[87]; }
char *play_cool() { return game_strings[88]; }
char *protest() { return game_strings[89]; }
char *steal_away() { return game_strings[90]; }
char *hold_still() { return game_strings[92]; }
char *stay_calm() { return game_strings[93]; }
char *make_suggestion() { return game_strings[94]; }
char *whats_in() { return game_strings[96]; }
char *no_way() { return game_strings[97]; }
char *push_it() { return game_strings[98]; }
char *fair_enough() { return game_strings[102]; }
char *keep_pushing() { return game_strings[103]; }
char *agree() { return game_strings[105]; }
char *disagree() { return game_strings[106]; }
char *let_her() { return game_strings[107]; }
char *intervene() { return game_strings[108]; }
char *prevent() { return game_strings[111]; }
char *do_as_told() { return game_strings[112]; }
char *up() { return game_strings[115]; }
char *down() { return game_strings[116]; }
char *guard() { return game_strings[136]; }
char *play_along() { return game_strings[137]; }
char *enter_offices() { return game_strings[117]; }
char *go_downstairs() { return game_strings[118]; }
char *alert_staff() { return game_strings[121]; }
char *make_call() { return game_strings[122]; }
char *squeal() { return game_strings[119]; }
char *keep_quiet() { return game_strings[120]; }
char *explain() { return game_strings[125]; }
char *lie() { return game_strings[126]; }
char *dial_999() { return game_strings[127]; }
char *give_hint() { return game_strings[129]; }
char *let_it_be() { return game_strings[138]; }
char *pick_it_up() { return game_strings[139]; }
char *warning() { return game_strings[143]; }
char *answer() { return game_strings[135]; }
char *dont() { return game_strings[140]; }
char *_do() { return game_strings[141]; }
char *enter_correct_key() { return game_strings[148]; }
char *enter_wrong_key() { return game_strings[149]; }
char *speak_up() { return game_strings[153]; }
char *high_five() { return game_strings[159]; }
char *smile() { return game_strings[161]; }
char *right() { return game_strings[165]; }
char *not_at_all() { return game_strings[166]; }
char *take_the_point() { return game_strings[156]; }
char *reply() { return game_strings[157]; }
char *dont_go_there() { return game_strings[169]; }
char *refuse() { return game_strings[160]; }
char *mr_woe() { return game_strings[177]; }
char *police() { return game_strings[178]; }
char *leave_her() { return game_strings[179]; }
char *convince_her() { return game_strings[180]; }
char *take_her() { return game_strings[182]; }
char *unsure() { return game_strings[183]; }
char *why_not() { return game_strings[185]; }
char *im_going() { return game_strings[186]; }
char *woe() { return game_strings[189]; }
char *fortune_cookie() { return game_strings[192]; }
char *follow_him() { return game_strings[193]; }
char *take_one() { return game_strings[195]; }
char *believe() { return game_strings[196]; }
char *disbelieve() { return game_strings[197]; }
char *accept() { return game_strings[198]; }
char *object() { return game_strings[199]; }
char *better_plan() { return game_strings[200]; }
char *go_to_police() { return game_strings[202]; }
char *follow_her() { return game_strings[203]; }
char *dont_mention_may() { return game_strings[209]; }
char *mention_may() { return game_strings[210]; }
char *kiss() { return game_strings[214]; }
char *withdraw() { return game_strings[215]; }
char *ask() { return game_strings[217]; }
char *open_window() { return game_strings[219]; }
char *_continue() { return game_strings[224]; }
char *upstairs() { return game_strings[220]; }
char *break_it() { return game_strings[221]; }
char *trust() { return game_strings[222]; }
char *dont_trust() { return game_strings[223]; }
char *go_back() { return game_strings[225]; }
char *long_one() { return game_strings[231]; }
char *short_one() { return game_strings[232]; }
char *protect_her() { return game_strings[233]; }
char *save_yourself() { return game_strings[234]; }
char *give_in() { return game_strings[235]; }
char *say_nothing() { return game_strings[241]; }
char *keep_protecting() { return game_strings[238]; }
char *trust_her() { return game_strings[244]; }
char *conditions() { return game_strings[246]; }
char *theres_nothing() { return game_strings[247]; }
char *dont_believe() { return game_strings[251]; }
char *reconsider() { return game_strings[248]; }
char *keep_walking() { return game_strings[249]; }
char *let_it_go() { return game_strings[252]; }
char *push_her() { return game_strings[255]; }
char *comfort_her() { return game_strings[256]; }
char *walk_away() { return game_strings[257]; }
char *kiss_her() { return game_strings[258]; }
char *keep_calm() { return game_strings[264]; }
char *fight() { return game_strings[265]; }
char *react() { return game_strings[269]; }
char *will() { return game_strings[260]; }
char *wont() { return game_strings[261]; }
char *insist() { return game_strings[277]; }
char *give_up() { return game_strings[278]; }
char *beg_her() { return game_strings[281]; }
char *bribe_her() { return game_strings[282]; }
char *keep_bluffing() { return game_strings[288]; }
char *maybe_keep_bluffing() { return game_vars.know_trojan ? game_strings[288] : NULL; }
char *physical_pressure() { return game_strings[289]; }
char *elevator() { return game_strings[286]; }
char *backstage() { return game_strings[287]; }
char *maybe_prove_it() { return game_vars.know_trojan ? game_strings[284] : NULL; }
char *maybe_hainsworths() { return game_vars.torture_seb ? game_strings[296] : NULL; }
char *hainsworths() { return game_strings[296]; }
char *stop() { return game_strings[292]; }
char *threaten_him() { return game_strings[291]; }
char *remove_oxygen() { return game_strings[293]; }
char *strangle_him() { return game_strings[295]; }
char *parrs() { return game_strings[299]; }
char *parr() { return game_strings[301]; }
char *auction_house() { return game_strings[320]; }
char *parrs_house() { return game_strings[321]; }

// Game possible variable values
enum {
	HERO_THINKS,
	LOSER_THINKS,
	FREAK_THINKS
};
enum {
	COOKIE_NO,
	COOKIE_REFUSED,
	COOKIE_OPENED,
};
enum {
	HOSPITAL_EP09B,
	PAYBACK_EP11,
};

// Game audio samples references
enum {
	// OPENING
	OPENING,
	ATMO_STATION,
	OPENING2,
	// EPISODE 1
	CAR_PARK,
	ATMO_GARAGE,
	CAR_PARK_MELODY,
	LEE_NOISE,
	CAR_PARK_DEAL,
	SCREAM_CLOSE,
	ELODIE_ESCAPE,
	LEE_STINGER,
	GARAGE_PARKFIELD,
	CABLE_TIE,
	SCREAM_FAR,
	CCTV,
	ROPE_LEE_STINGER,
	WEAPON_STINGER,
	CAR_PARK_NO_DEAL,
	INSIDE_CAR,
	MATT_ESCAPE,
	GUTTED_STINGER,
	// EPISODE 2
	ATMO_TRAIN,
	ATMO_TRAIN_STATION,
	LEE_LINE,
	JEFF_GUN,
	ATMO_HOUSE,
	SHOWDOWN_RISER,
	LETS_GO,
	ATMO_EXT_HOUSE,
	PUSHING_YOUR_CHANCE,
	ANY_SUGGESTIONS,
	LEG_IT,
	ONE_LESS_PROBLEM,
	JEFF_LINE,
	// EPISODE 3
	ATMO_BASEMENT_SEBASTIEN,
	CAR_PARK_ELEVATOR,
	HAIMSWORTH_STAIRS,
	ATMO_INSIDE_OFFICE,
	GET_AWAY_LONG,
	BIDDING_RISER_INTERVENE_1,
	BIDDING_RISER_INTERVENE_2,
	AWARENESS,
	BRUTAL_RISER,
	BRUTAL_CONSEQUENCE_1,
	BRUTAL_CONSEQUENCE_2,
	BRUTAL_CONSEQUENCE_3,
	HAIMSWORTH_ELEVATOR,
	ATMO_OUTSIDE_OFFICE,
	DANCE_CHERRY_BLOSSOMS,
	HAINSWORTH_OFFICE,
	ATMO_BASEMENT_GUARD,
	ATMO_AUCTION,
	ATMO_FREIGHT_LIFT_PING,
	VO_MATT_NO_MONEY,
	AWARENESS_DOWNLIFTER,
	BIDDING_RISER_LET_HER,
	BRUTAL_CONSEQUENCE_KEYPAD,
	ATMO_ENTRANCE,
	VO_MATT_MONEY,
	AUCTION_GUY,
	BIDDING_FLACHE,
	BOWL_AUCTION,
	GET_AWAY_RISER,
	HAINSWORTH_LOBBY,
	ATMO_ALARM,
	ATMO_HALL,
	TAKING_SEATS,
	// EPISODE 4
	ATMO_FORD_TRANSIT,
	AFTER_CRASH,
	ATMO_SIREN,
	ATMO_SIREN_2,
	ATMO_SIREN_3,
	GET_AWAY_SHORT,
	ATMO_BMW_M5,
	ATMO_BMW_I8,
	ATMO_LONDON,
	GET_AWAY_RISER_NEW,
	ATMO_FIRE,
	// EPISODE 5A
	ATMO_WOE_OFFICE,
	WOE_DARK,
	POLICE_EVERYWHERE,
	WOES_RESTO,
	PUSHING_YOUR_CHANCES,
	ATMO_HONG_KONG_BACK_DOOR,
	WOE_BOWL_MUSIC,
	ATMO_HONG_KONG_CITY,
	WOE_DARK_END,
	// EPISODE 5B
	SHOWDOWN_AND_VIOLENCE,
	RADIO_PLAY,
	TENSENESS,
	ATMO_POLICE_STATION,
	// EPISODE 6A
	ATMO_HOTEL_ROOM,
	TSCHOI_STAB,
	TSCHOI_ACTION,
	ATMO_TV_BG_PART1,
	ATMO_TV_BG_PART2,
	ATMO_TV_BG_PART3,
	ATMO_TV_BG_TRANS,
	ATMO_STAIRWAY,
	ATMO_BACKYARD,
	ON_THE_NEWS,
	HOTEL_ROMANCE,
	// EPISODE 6B
	TORTURE_TOM,
	TCHOI_HOTEL_ROOM,
	THUMBSCREW_P1,
	KNIFE_ACCENT_P1,
	KNIFE_ACCENT_P2,
	THUMBSCREW_TALK,
	HOELZLI_ACCENT,
	THUMBSCREW_P2,
	SHORT_KNIFE,
	LONG_KNIFE,
	ATMO_RADIO_PLAY,
	MATT_ALONE,
	TORTURE_MAIN,
	THUMBSCREW_ANGRY,
	TORTURE_END,
	// EPISODE 7
	FORGED,
	ATMO_TRAIN_REAR,
	DRUM_AND_BASS,
	ATMO_TRAIN_6,
	ATMO_TRAIN_5,
	MAYLING_TRUTH,
	ATMO_REVELLERS_4,
	POLICE_EVERYWHERE_1,
	POLICE_EVERYWHERE_2,
	ATMO_POLICE_SINGLE_SIREN,
	ATMO_POLICE_SINGLE_SIREN_2,
	ATMO_POLICE_SEVERAL_SIRENS,
	ATMO_TRAIN_5_BASS,
	ATMO_REVELLERS_3,
	ATMO_TRAIN_4_REAR,
	ATMO_TRAIN_1_LONGER,
	ATMO_TRAIN_5_LONGER,
	ATMO_REVELLERS_2,
	ATMO_TRAIN_4_LONGER,
	AFTER_FIGHT_TRANS,
	ATMO_REVELLERS_1,
	AFTER_FIGHT,
	ATMO_TRAIN_1,
	ATMO_TRAIN_2,
	ATMO_TUNNEL,
	ATMO_TRAIN_4_SHORT,
	ATMO_REVELLERS_5,
	ATMO_TRAIN_4,
	INTENTNESS_MOOD,
	// EPISODE 9A
	// EPISODE 9B
	// EPISODE 10
	// EPISODE 11
};
audio_sample *mus[NUM_AUDIO_SOURCES];

// Audio source purge lists per episode for non cross-episodic sounds that aren't explicitly freed by the game
void purge_from_ep1() {
	if (!fake_pass) {
		for (int i = CAR_PARK; i <= GUTTED_STINGER; i++) {
			if (i != MATT_ESCAPE) {
				audio_sample_stop_and_free(mus[i]);
			}
		}
	}
}
void purge_from_ep2() {
	if (!fake_pass) {
		for (int i = ATMO_TRAIN; i <= JEFF_LINE; i++) {
			if (i != LETS_GO) {
				audio_sample_stop_and_free(mus[i]);
			}
		}
	}
}
void purge_from_ep3() {
	if (!fake_pass) {
		for (int i = ATMO_BASEMENT_SEBASTIEN; i <= TAKING_SEATS; i++) {
			if (i != GET_AWAY_LONG) {
				audio_sample_stop_and_free(mus[i]);
			}
		}
	}
}
void purge_from_ep4() {
	if (!fake_pass) {
		for (int i = ATMO_FORD_TRANSIT; i <= ATMO_FIRE; i++) {
			if (i != AFTER_CRASH) {
				audio_sample_stop_and_free(mus[i]);
			}
		}
	}
}
void purge_from_ep5a() {
	if (!fake_pass) {
		for (int i = ATMO_WOE_OFFICE; i <= WOE_DARK_END; i++) {
			if (i != POLICE_EVERYWHERE && i != PUSHING_YOUR_CHANCES) {
				audio_sample_stop_and_free(mus[i]);
			}
		}
	}
}
void purge_from_ep5b() {
	if (!fake_pass) {
		audio_sample_stop_and_free(mus[SHOWDOWN_AND_VIOLENCE]);
		audio_sample_stop_and_free(mus[TENSENESS]);
		audio_sample_stop_and_free(mus[ATMO_POLICE_STATION]);
	}
}
void purge_from_ep6a() {
	if (!fake_pass) {
		for (int i = ATMO_HOTEL_ROOM; i <= HOTEL_ROMANCE; i++) {
			audio_sample_stop_and_free(mus[i]);
		}
	}
}
void purge_from_ep6b() {
	if (!fake_pass) {
		for (int i = TORTURE_TOM; i <= TORTURE_END; i++) {
			if (i != MATT_ALONE) {
				audio_sample_stop_and_free(mus[i]);
			}
		}
	}
}
void purge_from_ep7() {
	if (!fake_pass) {
		for (int i = FORGED; i <= INTENTNESS_MOOD; i++) {
			if (i != INTENTNESS_MOOD && i != AFTER_FIGHT_TRANS) {
				audio_sample_stop_and_free(mus[i]);
			}
		}
	}
}

// Game jump funcs
// OPENING
sequence *seg102_a() { return &sequences[1]; }
sequence *seg102_b() { return &sequences[2]; }
sequence *seg106() { return &sequences[3]; }
sequence *seg107_a() { return &sequences[4]; }
sequence *seg107_b() { return &sequences[5]; }
// EPISODE 1
sequence *seg109_110_b_111() { trigger_save = 1; return &sequences[6]; }
sequence *seg113_116() { return &sequences[7]; }
sequence *seg114() { return &sequences[8]; }
sequence *seg115() { game_vars.know_about_party = 1; return &sequences[9]; }
sequence *seg117() { return &sequences[13]; }
sequence *seg118() { return &sequences[11]; }
sequence *seg119() { game_vars.key_given = 1; return &sequences[12]; }
sequence *seg120() { return &sequences[24]; }
sequence *seg121() { game_vars.cctv_seg = 123; return &sequences[10]; }
sequence *seg128() { game_vars.cctv_seg = 130; return &sequences[14]; }
sequence *seg122_a_122_b() { return &sequences[16]; }
sequence *seg138_a_138_b() { game_vars.elo_thinks = LOSER_THINKS; return &sequences[21]; }
sequence *seg141() { game_vars.elo_thinks = HERO_THINKS; return &sequences[18]; }
sequence *eval_has_pepper() { return game_vars.has_pepper_spray ? &sequences[18] : &sequences[19]; }
sequence *eval_has_pepper_def() { return game_vars.has_pepper_spray ? seg141() : seg138_a_138_b(); }
sequence *seg133_swipe() { return &sequences[22]; }
sequence *seg134_1() { game_vars.has_pepper_spray = 1; return &sequences[23]; }
sequence *seg140() { return &sequences[25]; }
sequence *seg123() { return &sequences[26]; }
sequence *seg123_tap_130_tap() { return &sequences[27]; }
sequence *seg129() { return &sequences[15]; }
sequence *eval_cctv_seg() { return game_vars.cctv_seg == 123 ? seg122_a_122_b() : seg129(); }
sequence *seg127() { return &sequences[29]; }
sequence *seg135() { return &sequences[28]; }
sequence *seg142() { return &sequences[30]; }
sequence *seg143() { return &sequences[31]; }
sequence *seg144() { return &sequences[32]; }
sequence *seg145_swipe() { return &sequences[33]; }
sequence *seg148_b() { game_vars.with_lee = 1; return &sequences[34]; }
sequence *seg146_a() { game_vars.matt_escape = 1; return &sequences[35]; }
sequence *seg147_a_148_a() { return &sequences[36]; }
sequence *seg147_b() { game_vars.with_lee = 0; return &sequences[37]; }
sequence *seg126() { return &sequences[38]; }
sequence *seg137() { return &sequences[20]; }
sequence *seg136() { return &sequences[17]; }
sequence *seg134_2() { return &sequences[39]; }
sequence *seg125() { game_vars.elo_thinks = FREAK_THINKS; return &sequences[40]; }
sequence *seg112_2_122_b() { game_vars.elo_thinks = FREAK_THINKS; return &sequences[213]; }
sequence *seg112_1() { return &sequences[212]; }
// EPISODE 2
sequence *seg201() { trigger_save = 1; purge_from_ep1(); return &sequences[41]; }
sequence *seg202() { trigger_save = 1; purge_from_ep1(); return &sequences[42]; }
sequence *seg203() { return &sequences[43]; }
sequence *seg204() { return &sequences[44]; }
sequence *seg205() { return &sequences[45]; }
sequence *seg206() { return &sequences[46]; }
sequence *seg207() { return &sequences[47]; }
sequence *seg202_1() { return &sequences[48]; }
sequence *seg209() { return &sequences[49]; }
sequence *seg210() { return &sequences[50]; }
sequence *seg208_213_214() { return &sequences[51]; }
sequence *seg215() { return &sequences[52]; }
sequence *seg216() { return &sequences[53]; }
sequence *seg217() { return &sequences[54]; }
sequence *seg218() { return &sequences[55]; }
sequence *seg219() { return &sequences[56]; }
sequence *seg220_1() { game_vars.coming_from_seg223 = 0; return &sequences[57]; }
sequence *seg220_2() { return &sequences[58]; }
sequence *seg223() { game_vars.coming_from_seg223 = 1; return &sequences[59]; }
sequence *seg224() { game_vars.coming_from_seg223 = 0; return &sequences[60]; }
sequence *seg225() { return &sequences[61]; }
sequence *seg226_1() { return &sequences[62]; }
sequence *seg226() { return &sequences[63]; }
sequence *seg212() { return &sequences[64]; }
sequence *seg230() { return &sequences[65]; }
sequence *seg231() { game_vars.may_likes_matt++; game_vars.respect_earned = 1; return &sequences[69]; }
sequence *eval_coming_from_seg223() { return game_vars.coming_from_seg223 ? seg231() : &sequences[67]; }
sequence *seg227() { return &sequences[68]; }
sequence *seg228() { return &sequences[66]; }
// EPISODE 3
sequence *seg301_1_301_2() { trigger_save = 1; purge_from_ep2(); return &sequences[70]; }
sequence *seg302_a() { game_vars.may_likes_matt++; return &sequences[71]; }
sequence *seg302_b() { game_vars.sabotage++; return &sequences[72]; }
sequence *seg303_310() { return &sequences[73]; }
sequence *seg314_1() { if (chosen_path == 2) return &sequences[76]; else return NULL; }
sequence *seg314_2() { return &sequences[77]; }
sequence *seg311() { game_vars.sabotage++; game_vars.may_likes_matt++; return &sequences[74]; }
sequence *seg312() { game_vars.intervened = 1; game_vars.sold_for = 9; return &sequences[75]; }
sequence *seg313() { game_vars.sabotage++; game_vars.may_likes_matt++; game_vars.sold_for = 13; return &sequences[78]; }
sequence *eval_intervened() { return game_vars.intervened ? &sequences[80] : &sequences[81]; }
sequence *eval_intervened2() { return game_vars.intervened ? &sequences[84] : &sequences[85]; }
sequence *seg318() { return &sequences[83]; }
sequence *seg317() { return &sequences[82]; }
sequence *seg315() { return &sequences[79]; }
sequence *seg314() { game_vars.intervened = 1; game_vars.sold_for = 12; return &sequences[86]; }
sequence *seg345() { return &sequences[87]; }
sequence *seg319() { game_vars.sabotage++; game_vars.gone_upstairs = 1; return &sequences[88]; }
sequence *seg320_swipe() { return &sequences[89]; }
sequence *seg322() { return &sequences[90]; }
sequence *seg322_tap() { return &sequences[91]; }
sequence *seg326_324() { game_vars.passed_by_seg326 = 1; return &sequences[92]; }
sequence *seg327() { return &sequences[93]; }
sequence *seg328() { return &sequences[94]; }
sequence *seg329() { return &sequences[95]; }
sequence *seg329_1() { return &sequences[96]; }
sequence *seg331() { return &sequences[97]; }
sequence *seg333() { game_vars.sabotage++; return &sequences[98]; }
sequence *seg346_350_352() { return &sequences[99]; }
sequence *seg354() { return &sequences[100]; }
sequence *seg365_366() { game_vars.sabotage++; game_vars.passed_by_seg341 = 0; return &sequences[101]; }
sequence *seg365_366_double() { game_vars.sabotage += 2; game_vars.passed_by_seg341 = 0; return &sequences[101]; }
sequence *seg342() { game_vars.lockdown = 1; game_vars.get_away_long_playing = 1; return &sequences[102]; }
sequence *seg335() { return &sequences[103]; }
sequence *seg341() { game_vars.passed_by_seg341 = 1; return &sequences[104]; }
sequence *eval_security_alert() { return game_vars.security_alert ? seg341() : &sequences[105]; }
sequence *seg339() { game_vars.sabotage++; return &sequences[106]; }
sequence *seg340() { game_vars.lockdown = 1; game_vars.get_away_long_playing = 1; return &sequences[107]; }
sequence *seg330() { game_vars.security_alert = 1; return &sequences[108]; }
sequence *seg349_355_356() { return &sequences[109]; }
sequence *seg357() { return &sequences[110]; }
sequence *seg358_359() { return &sequences[111]; }
sequence *eval_sabotage() { return game_vars.sabotage >= 3 ? &sequences[112] : &sequences[113]; }
sequence *seg321_324() { return &sequences[114]; }
sequence *seg325_a() { game_vars.sabotage++; return &sequences[115]; }
sequence *seg325_b() { return &sequences[116]; }
sequence *seg334() { return &sequences[117]; }
sequence *seg336() { return &sequences[118]; }
sequence *seg337() { game_vars.sabotage++; game_vars.security_alert = 1; return &sequences[119]; }
sequence *seg360() { return &sequences[120]; }
sequence *seg361() { return &sequences[121]; }
sequence *seg362() { return &sequences[122]; }
sequence *seg363() { return &sequences[123]; }
sequence *seg369_1k() { return &sequences[124]; }
sequence *seg369_2k() { return &sequences[125]; }
sequence *seg370_375() { game_vars.lockdown = 0; game_vars.get_away_long_playing = 1; return &sequences[126]; }
sequence *seg373_374_366() { return &sequences[127]; }
// EPISODE4
sequence *eval_ep4_start() { trigger_save = 1; purge_from_ep3(); if (game_vars.lockdown) { return (game_vars.gone_upstairs || game_vars.sabotage >= 4) ? &sequences[128] : &sequences[129]; } else return game_vars.gone_upstairs ? &sequences[130] : &sequences[131]; }
sequence *eval_low_sabotage() { return game_vars.sabotage < 3 ? &sequences[132] : &sequences[133]; }
sequence *seg408() { game_vars.may_likes_matt++; return &sequences[134]; }
sequence *seg403_a() { return &sequences[135]; }
sequence *seg403_b() { game_vars.blank_book = 1; return &sequences[136]; }
sequence *seg404_a() { return &sequences[137]; }
sequence *seg404_b() { game_vars.may_likes_matt++; return &sequences[138]; }
sequence *seg407_c() { return &sequences[139]; }
sequence *seg409() { game_vars.may_likes_matt++; return &sequences[140]; }
sequence *seg410() { game_vars.blank_book = 1; return &sequences[141]; }
sequence *seg411_a() { return &sequences[142]; }
sequence *seg411_b() { game_vars.may_likes_matt++; return &sequences[143]; }
sequence *seg412() { return &sequences[144]; }
sequence *seg413() { return &sequences[145]; }
sequence *seg417_a() { return &sequences[146]; }
sequence *seg417_b() { return &sequences[147]; }
sequence *seg405() { game_vars.may_likes_matt++; return &sequences[148]; }
sequence *seg419() { return &sequences[149]; }
sequence *seg414() { return &sequences[150]; }
sequence *seg420() { return &sequences[151]; }
sequence *seg421_a() { return &sequences[152]; }
sequence *seg435_a() { return &sequences[154]; }
sequence *seg434() { return &sequences[153]; }
sequence *seg435_b() { return &sequences[155]; }
sequence *seg435_c() { return &sequences[156]; }
sequence *seg436_437() { return &sequences[157]; }
sequence *seg438() { return &sequences[158]; }
sequence *seg439_a() { return &sequences[159]; }
sequence *seg439_b() { return &sequences[160]; }
sequence *seg439_c() { return &sequences[161]; }
sequence *seg440() { return &sequences[162]; }
sequence *seg441() { return &sequences[163]; }
sequence *seg442() { return &sequences[164]; }
sequence *seg443() { return &sequences[165]; }
sequence *seg444() { return &sequences[166]; }
sequence *seg445() { return &sequences[167]; }
sequence *seg445_1() { return &sequences[168]; }
sequence *seg446() { return &sequences[169]; }
sequence *seg447() { game_vars.gone_to_woe = 1; return &sequences[170]; }
sequence *seg442_1() { return &sequences[171]; }
// EPISODE 5A
sequence *seg501_507() { trigger_save = 1; purge_from_ep4(); return &sequences[172]; }
sequence *seg508_1() { return &sequences[173]; }
sequence *seg508_2() { game_vars.has_cookie = COOKIE_REFUSED; return &sequences[174]; }
sequence *seg508_3() { game_vars.has_cookie = COOKIE_OPENED; return &sequences[175]; }
sequence *seg509_511() { return &sequences[176]; }
sequence *seg516() { return &sequences[177]; }
sequence *seg517() { return &sequences[178]; }
sequence *seg519() { return &sequences[179]; }
sequence *seg520() { return &sequences[180]; }
sequence *seg522() { return &sequences[181]; }
sequence *eval_cookie() { if (game_vars.has_cookie) { return game_vars.has_cookie == COOKIE_REFUSED ? &sequences[182] : &sequences[184]; } else return &sequences[183]; }
sequence *seg525() { return &sequences[185]; }
sequence *seg526() { return &sequences[186]; }
sequence *seg527() { return &sequences[187]; }
sequence *seg528_a() { return &sequences[188]; }
sequence *seg528_b() { return &sequences[189]; }
sequence *seg529_a() { return &sequences[190]; }
sequence *seg529_b() { return &sequences[191]; }
sequence *seg530() { return &sequences[192]; }
// EPISODE 5B
sequence *seg551() { trigger_save = 1; purge_from_ep4(); purge_from_ep5a(); return &sequences[193]; }
sequence *seg554() { if (!game_vars.gone_to_woe) trigger_save = 1; game_vars.report_to_police = 1; return &sequences[194]; }
sequence *eval_gone_to_woe() { return game_vars.gone_to_woe ? &sequences[195] : &sequences[196]; }
sequence *eval_sabotage2() { return game_vars.sabotage >= 4 ? &sequences[197] : &sequences[198]; }
sequence *seg557() { return &sequences[199]; }
sequence *seg558_a() { return &sequences[200]; }
sequence *seg558_b() { return &sequences[201]; }
sequence *seg560() { return &sequences[202]; }
sequence *seg562_a() { return &sequences[203]; }
sequence *seg562_b() { return &sequences[204]; }
sequence *seg563() { return &sequences[205]; }
sequence *seg564_a() { return &sequences[206]; }
sequence *seg564_b() { return &sequences[207]; }
sequence *seg565() { return &sequences[208]; }
sequence *eval_gone_to_woe2() { return game_vars.gone_to_woe ? &sequences[209] : &sequences[210]; }
sequence *seg570_571() { return &sequences[211]; }
// EPISODE 6A
sequence *seg601_602_603() { purge_from_ep5a(); trigger_save = 1; return &sequences[214]; }
sequence *eval_blank_book() { return game_vars.blank_book ? &sequences[215] : &sequences[216]; }
sequence *eval_may_likes_matt() { if (game_vars.may_likes_matt >= 4) { game_vars.may_kiss = 1; return &sequences[233]; } return &sequences[234]; }
sequence *eval_may_kiss() { return game_vars.may_kiss ? &sequences[236] : &sequences[235]; }
sequence *seg605_b() { return &sequences[217]; }
sequence *seg606() { return &sequences[218]; }
sequence *seg607() { return &sequences[219]; }
sequence *seg610() { return &sequences[221]; }
sequence *seg608() { return &sequences[220]; }
sequence *seg614_b() { return &sequences[223]; }
sequence *seg614_a() { return &sequences[222]; }
sequence *seg615() { return &sequences[225]; }
sequence *seg618() { return &sequences[224]; }
sequence *seg619() { return &sequences[226]; }
sequence *seg616_622() { return &sequences[228]; }
sequence *seg620_621_622() { return &sequences[227]; }
sequence *seg617() { return &sequences[229]; }
sequence *seg623_a() { return &sequences[230]; }
sequence *seg623_b() { return &sequences[231]; }
sequence *seg624() { game_vars.radioplay_started = 1; return &sequences[232]; }
// EPISODE 6B
sequence *seg651_1() { purge_from_ep5b(); purge_from_ep6a(); trigger_save = 1; game_vars.cross_exam = 1; return &sequences[237]; }
sequence *eval_report_police() { return game_vars.report_to_police ? &sequences[238] : &sequences[239]; }
sequence *seg651_3() { return &sequences[240]; }
sequence *seg652_a() { return &sequences[241]; }
sequence *seg652_b() { return &sequences[242]; }
sequence *seg653() { game_vars.thumb_pain = 1; return &sequences[243]; }
sequence *seg654() { return &sequences[244]; }
sequence *seg655_a() { game_vars.knife_long = 0; return &sequences[245]; }
sequence *seg655_b() { game_vars.knife_long = 1; return &sequences[246]; }
sequence *seg655_c() { game_vars.knife_long = 1; return &sequences[247]; }
sequence *seg656() { return &sequences[248]; }
sequence *seg666_a() { return &sequences[249]; }
sequence *seg657() { return &sequences[250]; }
sequence *seg673() { return &sequences[254]; }
sequence *eval_may_likes_matt2() { if (game_vars.may_likes_matt >= 1) return &sequences[251]; if (game_vars.knife_long) return &sequences[252]; return &sequences[253]; }
sequence *eval_spit_in_the_face() { return game_vars.spit_in_the_face ? &sequences[255] : &sequences[256]; }
sequence *seg672() { game_vars.matt_alone_playing = 1; return &sequences[257]; }
sequence *seg661() { return &sequences[258]; }
sequence *seg674() { game_vars.matt_alone_playing = 1; game_vars.may_stabbed = 1; return &sequences[259]; }
sequence *seg675() { return &sequences[260]; }
sequence *eval_may_likes_matt3() { if (game_vars.may_likes_matt >= 2) return &sequences[261]; if (game_vars.knife_long) return &sequences[252]; return &sequences[253]; }
sequence *seg666_b() { return &sequences[262]; }
sequence *seg663() { return &sequences[263]; }
sequence *eval_may_likes_matt4() { if (game_vars.may_likes_matt >= 3) return &sequences[264]; if (game_vars.knife_long) return &sequences[252]; return &sequences[253]; }
sequence *seg665() { game_vars.spit_in_the_face = 1; return &sequences[265]; }
sequence *seg666_c() { return &sequences[266]; }
sequence *eval_knife_long() { return game_vars.knife_long ? &sequences[267] : &sequences[268]; }
// EPISODE 7
sequence *eval_ep7_start() { purge_from_ep6a(); purge_from_ep6b();  trigger_save = 1; return game_vars.cross_exam ? &sequences[269] : &sequences[270]; }
sequence *seg702() { return &sequences[271]; }
sequence *seg707() { return &sequences[272]; }
sequence *seg703() { game_vars.turned_away = 1; return &sequences[273]; }
sequence *seg704() { return &sequences[274]; }
sequence *seg708() { return &sequences[275]; }
sequence *seg709() { return &sequences[276]; }
sequence *seg710() { return &sequences[277]; }
sequence *seg711() { game_vars.left_may_crying = 1; return &sequences[278]; }
sequence *seg712() { return &sequences[279]; }
sequence *eval_may_kissed_matt() { if (game_vars.may_kiss || game_vars.may_likes_matt > 3) return &sequences[280]; else return &sequences[281];  }
sequence *seg713_c() { return &sequences[282]; }
sequence *seg714_723() { return &sequences[283]; }
sequence *seg724() { return &sequences[284]; }
sequence *seg760() { return &sequences[285]; }
sequence *seg761() { return &sequences[286]; }
sequence *seg762() { return &sequences[287]; }
sequence *seg763() { return &sequences[288]; }
sequence *seg764() { return &sequences[289]; }
sequence *seg725_k() { return &sequences[290]; }
sequence *seg727() { return &sequences[291]; }
sequence *seg734() { return &sequences[292]; }
sequence *eval_left_may_crying() { return game_vars.left_may_crying ? &sequences[293] : &sequences[294]; }
sequence *seg739_1() { return &sequences[295]; }
sequence *seg739_a() { game_vars.passed_by_seg739 = 1; return &sequences[296]; }
sequence *seg739_b() { game_vars.from_ep7_to_ep11 = 1; game_vars.from_ep9_to_ep11 = 1; return &sequences[297]; }
sequence *eval_cross_exam() { return game_vars.cross_exam ? seg739_b() : seg739_a(); }
sequence *seg733() { return &sequences[298]; }
sequence *seg715() { return &sequences[299]; }
sequence *eval_turned_away() { return game_vars.turned_away ? &sequences[300] : &sequences[301]; }
sequence *seg719_720() { return &sequences[302]; }
sequence *seg716_723() { return &sequences[303]; }
sequence *seg721_723() { return &sequences[304]; }
sequence *seg737() { return &sequences[305]; }
sequence *seg738() { return &sequences[306]; }
sequence *seg740() { return &sequences[307]; }
sequence *seg741() { return &sequences[308]; }
sequence *seg742() { return &sequences[309]; }
sequence *seg743_k() { return &sequences[310]; }
sequence *seg743_1() { return &sequences[311]; }
sequence *seg745() { game_vars.finish_ep7_target = HOSPITAL_EP09B; return &sequences[312]; }
sequence *seg747_2_749_750() { game_vars.finish_ep7_target = PAYBACK_EP11; game_vars.from_ep7_to_ep11 = 1; game_vars.from_ep9_to_ep11 = 1; return &sequences[313]; }
sequence *seg765_756_757() { game_vars.finish_ep7_target = PAYBACK_EP11; game_vars.from_ep7_to_ep11 = 1; game_vars.from_ep9_to_ep11 = 1; game_vars.passed_by_seg765 = 1; return &sequences[314]; }
sequence *seg770() { return &sequences[315]; }
sequence *eval_ep7_target() { return game_vars.finish_ep7_target == PAYBACK_EP11 ? NULL : seg951_1_951_2(); }
sequence *seg770_2() { return &sequences[316]; }
// EPISODE 9A
sequence *seg901_1_901_2() { trigger_save = 1; return &sequences[317]; }
sequence *eval_gone_upstairs() { return game_vars.gone_upstairs ? &sequences[337] : &sequences[338]; }
sequence *seg905_2() { return &sequences[328]; }
sequence *seg908_b() { return &sequences[332]; }
sequence *seg918() { return &sequences[339]; }
sequence *seg919() { return &sequences[340]; }
sequence *seg910() { return &sequences[333]; }
sequence *seg920() { return &sequences[341]; }
sequence *seg914() { game_vars.know_trojan = 1; return &sequences[342]; }
sequence *seg915() { return &sequences[335]; }
sequence *seg916() { return &sequences[336]; }
sequence *seg912_913() { return &sequences[334]; }
sequence *eval_key_elo() { return game_vars.key_given ? &sequences[326] : &sequences[327]; }
sequence *eval_key_given() { return game_vars.key_given ? &sequences[330] : &sequences[331]; }
sequence *eval_hero() { return game_vars.elo_thinks == HERO_THINKS ? &sequences[324] : &sequences[325]; }
sequence *eval_loser() { return game_vars.elo_thinks == LOSER_THINKS ? &sequences[322] : &sequences[323]; }
sequence *eval_freak() { return game_vars.elo_thinks == FREAK_THINKS ? &sequences[320] : &sequences[321]; }
sequence *eval_knows_about_party() { return game_vars.know_about_party ? &sequences[318] : &sequences[319]; }
sequence *seg911_913() { return &sequences[343]; }
sequence *seg907_2() { return &sequences[329]; }
sequence *seg947_1_913() { return &sequences[344]; }
sequence *seg948_1() { return &sequences[345]; }
sequence *seg921() { return &sequences[346]; }
sequence *seg922() { return &sequences[347]; }
sequence *seg927() { game_vars.mentioned_trojan = 1; return &sequences[350]; }
sequence *seg928() { return &sequences[351]; }
sequence *seg929() { return &sequences[353]; }
sequence *seg930() { return &sequences[354]; }
sequence *seg936() { game_vars.payback_time = 1; return &sequences[359]; }
sequence *seg928_939() { return &sequences[352]; }
sequence *seg930_939() { return &sequences[355]; }
sequence *seg929_939() { return &sequences[357]; }
sequence *seg931_933_934_a_935() { game_vars.torture_seb = 1; return &sequences[356]; }
sequence *eval_mentioned_trojan() { return game_vars.mentioned_trojan ? &sequences[348]: &sequences[349]; }
sequence *seg933_2_937_a_938() { game_vars.got_keycard = 1; game_vars.aware_of_chest = 1; game_vars.payback_time = 0; return &sequences[358]; }
sequence *seg937_a_938() { game_vars.got_keycard = 1; game_vars.aware_of_chest = 1; return &sequences[360]; }
sequence *seg937_b_938() { game_vars.aware_of_chest = 1; return &sequences[361]; }
sequence *seg939() { game_vars.payback_time = 0; game_vars.called_parr = 1; return &sequences[362]; }
sequence *seg945() { return &sequences[363]; }
sequence *eval_payback_time() { return game_vars.payback_time ? /* ep11 */ NULL : /* ep10 */ NULL; }
// EPISODE 9B
sequence *seg951_1_951_2() { trigger_save = 1; purge_from_ep7(); return &sequences[364]; }
sequence *eval_knows_about_party2() { return game_vars.know_about_party ? &sequences[365] : &sequences[366]; }
sequence *eval_freak2() { return game_vars.elo_thinks == FREAK_THINKS ? &sequences[367] : &sequences[368]; }
sequence *eval_loser2() { return game_vars.elo_thinks == LOSER_THINKS ? &sequences[369] : &sequences[370]; }
sequence *eval_hero2() { return game_vars.elo_thinks == HERO_THINKS ? &sequences[372] : &sequences[373]; }
sequence *eval_freak3() { return game_vars.elo_thinks == FREAK_THINKS ? &sequences[374] : &sequences[375]; }
sequence *eval_key_given2() { return game_vars.key_given ? &sequences[377] : &sequences[378]; }
sequence *seg948_2() { return &sequences[376]; }
sequence *seg955() { return &sequences[371]; }
sequence *seg957_2() { return &sequences[380]; }
sequence *seg958_b() { return &sequences[379]; }
sequence *seg960() { return &sequences[381]; }
sequence *seg961() { return &sequences[382]; }
sequence *seg962() { return &sequences[383]; }
sequence *seg963() { game_vars.know_trojan = 1; return &sequences[384]; }
sequence *seg964() { return &sequences[385]; }
sequence *seg965() { return &sequences[386]; }
sequence *eval_gone_upstairs2() { return game_vars.gone_upstairs ? &sequences[387] : &sequences[388]; }
sequence *seg967() { return &sequences[389]; }
sequence *seg968() { return &sequences[390]; }
sequence *seg969_a() { return &sequences[391]; }
sequence *seg969_b() { return &sequences[392]; }
sequence *seg970() { return &sequences[393]; }
sequence *eval_passed_by_seg975() { return game_vars.passed_by_seg975 ? &sequences[394] : &sequences[395]; }
sequence *eval_know_trojan() { return game_vars.know_trojan ? &sequences[396] : &sequences[397]; }
sequence *seg974_1() { return &sequences[398]; }
sequence *seg974() { return &sequences[399]; }
sequence *seg975() { game_vars.passed_by_seg975 = 1; return &sequences[400]; }
sequence *seg976() { return &sequences[401]; }
sequence *eval_know_trojan2() { game_vars.torture_seb = 1; game_vars.aware_of_chest = 1; return game_vars.know_trojan ? &sequences[402] : &sequences[403]; }
sequence *seg972() { return &sequences[404]; }
sequence *seg977_978() { return &sequences[405]; }
sequence *eval_thumb_pain() { game_vars.got_keycard = 1; return game_vars.thumb_pain ? &sequences[406] : &sequences[407]; }
sequence *seg994() { return &sequences[408]; }
sequence *eval_cross_exam3() { if (game_vars.cross_exam) { game_vars.from_ep9_to_ep11 = 0; return NULL; /* ep10 */ } return seg994(); }
sequence *eval_cross_exam2() { if (game_vars.cross_exam) { game_vars.from_ep9_to_ep11 = 1; return NULL; /* ep11 */ } return seg994(); }
sequence *eval_payback_time2() { if (game_vars.payback_time) { game_vars.from_ep9_to_ep11 = 1; return NULL; /* ep 11 */ } game_vars.from_ep9_to_ep11 = 0; return NULL; /* ep10 */ }
sequence *seg988_984_2() { game_vars.payback_time = 1; return &sequences[409]; }
sequence *seg974_2() { return &sequences[410]; }
sequence *seg977_979() { game_vars.aware_of_chest = 1; return &sequences[411]; }
// EPISODE 10
// EPISODE 11

// Game event funcs
sequence *seg435_a_event() { if (game_vars.may_likes_matt >= 4) { return seg435_a(); } return NULL; }
sequence *start_op_bgm() { mus[OPENING] = audio_sample_start("EP01 Opening", 0, 0.20033f); return NULL; }
sequence *fade_op_vol_1() { audio_sample_set_volume(mus[OPENING], 0.125887f); return NULL; }
sequence *fade_op_vol_2() { audio_sample_set_volume(mus[OPENING], 0.198939f); return NULL; }
sequence *fade_op_vol_3() { audio_sample_set_volume(mus[OPENING], 0.126269f); return NULL; }
sequence *fade_op_vol_4() { audio_sample_set_volume(mus[OPENING], 0.199322f); return NULL; }
sequence *fade_op_vol_5() { audio_sample_set_volume(mus[OPENING], 0.124558f); return NULL; }
sequence *fade_op_vol_6() { audio_sample_set_volume(mus[OPENING], 0.198644f); return NULL; }
sequence *start_atmo_station() { mus[ATMO_STATION] = audio_sample_start("EP01 Atmo Int Tube Station", 0, 1.0f); return NULL; }
sequence *start_selfish_title() { mus[OPENING2] = audio_sample_start("EP01 Titles SelfFish", 0, 0.3178015f); return NULL; }
sequence *start_selfless_title() { mus[OPENING2] = audio_sample_start("EP01 Titles SelfLess", 0, 0.3161767f); return NULL; }
sequence *fade_out_op() { audio_sample_fade(mus[OPENING], 0.198644f, 0.0f, 10750, 14750); return NULL; }
sequence *fade_out_op2() { audio_sample_fade(mus[OPENING], 0.198644f, 0.0f, 0, 4000); return NULL; }
sequence *fade_out_atmo_station() { audio_sample_fade(mus[ATMO_STATION], 1.0f, 0.0f, 19417, 24500); return NULL; }
sequence *fade_out_atmo_station2() { audio_sample_fade(mus[ATMO_STATION], 1.0f, 0.0f, 17792, 23000); return NULL; }
sequence *stop_opening() { audio_sample_stop_and_free(mus[OPENING]); return NULL; }
sequence *stop_atmo_station() { audio_sample_stop_and_free(mus[ATMO_STATION]); return NULL; }
sequence *start_loneliness_carpark() { mus[CAR_PARK] = audio_sample_start("EP01 Loneliness Carpark Neu", 0, 0.1110497f); return NULL; }
sequence *start_garage_atmo() { mus[ATMO_GARAGE] = audio_sample_start("EP01 Atmo Int Garage Hut", 1, 1.0f); return NULL; }
sequence *stop_atmo_garage() { audio_sample_stop_and_free(mus[ATMO_GARAGE]); return NULL; }
sequence *start_car_park_melody() { mus[CAR_PARK_MELODY] = audio_sample_start("EP01 Car Park Melody", 0, 0.1767543f); return NULL; }
sequence *stop_opening2() { audio_sample_stop_and_free(mus[OPENING2]); return NULL; }
sequence *fade_car_park_melody() { audio_sample_fade(mus[CAR_PARK_MELODY], 0.1767543f, 0.0f, 2333, 7750); return NULL; }
sequence *fade_car_park_melody2() { audio_sample_fade(mus[CAR_PARK_MELODY], 0.1767543f, 0.0f, 10875, 18875); return NULL; }
sequence *fade_car_park_melody3() { audio_sample_fade(mus[CAR_PARK_MELODY], 0.1767543f, 0.0f, 4667, 12667); return NULL; }
sequence *fade_car_park_melody4() { audio_sample_fade(mus[CAR_PARK_MELODY], 0.1767543f, 0.0f, 41, 3625); return NULL; }
sequence *fade_car_park_melody5() { audio_sample_fade(mus[CAR_PARK_MELODY], 0.1767543f, 0.0f, 42, 7042); return NULL; }
sequence *start_lee_noise() { mus[LEE_NOISE] = audio_sample_start("EP01 Lee's Noise", 0, 0.2506548f); return NULL; }
sequence *start_lee_noise2() { mus[LEE_NOISE] = audio_sample_start("EP01 Lee's Noise", 0, 0.2514759f); return NULL; }
sequence *start_lee_noise3() { mus[LEE_NOISE] = audio_sample_start("EP01 Lee's Noise", 0, 0.2517725f); return NULL; }
sequence *stop_carpark_melody() { audio_sample_stop_and_free(mus[CAR_PARK_MELODY]); return NULL; }
sequence *start_carpark_deal() { mus[CAR_PARK_DEAL] = audio_sample_start("EP01 Carpark Deal", 0, 0.1579017f); return NULL; }
sequence *start_scream_close() { mus[SCREAM_CLOSE] = audio_sample_start("EP01 Atmo Scream Close", 0, 0.1635859f); return NULL; }
sequence *stop_carpark_deal() { audio_sample_stop_and_free(mus[CAR_PARK_DEAL]); return NULL; }
sequence *start_elodie_escape() { mus[ELODIE_ESCAPE] = audio_sample_start("EP01 Elodie Escape", 0, 0.1770804f); return NULL; }
sequence *start_elodie_escape2() { mus[ELODIE_ESCAPE] = audio_sample_start("EP01 Elodie Escape", 0, 0.1769967f); return NULL; }
sequence *fade_car_park_deal() { audio_sample_fade(mus[CAR_PARK_DEAL], 0.1579017f, 0.0f, 6917, 7917); return NULL; }
sequence *fade_car_park_deal2() { audio_sample_fade(mus[CAR_PARK_DEAL], 0.1579017f, 0.0f, 11500, 12500); return NULL; }
sequence *start_lee_stinger() { mus[LEE_STINGER] = audio_sample_start("EP01 Lee Stinger", 0, 0.1989933f); return NULL; }
sequence *start_garage_parkfield() { mus[GARAGE_PARKFIELD] = audio_sample_start("EP01 Atmo Int Garage Parkfield", 1, 1.0f); return NULL; }
sequence *start_cable_tie() { mus[CABLE_TIE] = audio_sample_start("EP01 Cable Tie Stinger", 0, 0.1998071f); return NULL; }
sequence *start_scream_far() { mus[SCREAM_FAR] = audio_sample_start("EP01 Atmo Scream Far", 0, 1.0f); return NULL; }
sequence *start_cctv() { mus[CCTV] = audio_sample_start("EP01 CCTV", 0, 0.2512645f); return NULL; }
sequence *start_rope_lee_stinger() { mus[ROPE_LEE_STINGER] = audio_sample_start("EP01 Rope Lee Stinger", 0, 0.1274621f); return NULL; }
sequence *start_weapon_stinger() { mus[WEAPON_STINGER] = audio_sample_start("EP01 Weapon Stinger", 0, 0.1760814f); return NULL; }
sequence *start_weapon_stinger2() { mus[WEAPON_STINGER] = audio_sample_start("EP01 Weapon Stinger", 0, 0.1752229f); return NULL; }
sequence *start_carpark_nodeal() { mus[CAR_PARK_NO_DEAL] = audio_sample_start("EP01 Carpark NoDeal", 0, 0.1246213f); return NULL; }
sequence *start_carpark_nodeal2() { mus[CAR_PARK_NO_DEAL] = audio_sample_start("EP01 Carpark NoDeal", 0, 0.1274091f); return NULL; }
sequence *start_carpark_nodeal3() { mus[CAR_PARK_NO_DEAL] = audio_sample_start("EP01 Carpark NoDeal", 0, 0.1262329f); return NULL; }
sequence *fade_garage_parkfield() { audio_sample_fade(mus[GARAGE_PARKFIELD], 1.0f, 0.0f, 19958, 22250); return NULL; }
sequence *stop_garage_parkfield() { audio_sample_stop_and_free(mus[GARAGE_PARKFIELD]); return NULL; }
sequence *stop_carpark_nodeal() { audio_sample_stop_and_free(mus[CAR_PARK_NO_DEAL]); return NULL; }
sequence *stop_elodie_escape() { audio_sample_stop_and_free(mus[ELODIE_ESCAPE]); return NULL; }
sequence *start_inside_car() { mus[INSIDE_CAR] = audio_sample_start("EP01 Inside Car", 0, 0.2504064f); return NULL; }
sequence *start_matt_escape() { mus[MATT_ESCAPE] = audio_sample_start("EP01 Matt Escape", 0, 0.1586634f); return NULL; }
sequence *stop_inside_car() { audio_sample_stop_and_free(mus[INSIDE_CAR]); return NULL; }
sequence *fade_inside_car() { audio_sample_fade(mus[INSIDE_CAR], 0.2504064f, 0.0f, 41, 3042); return NULL; }
sequence *fade_inside_car2() { audio_sample_fade(mus[INSIDE_CAR], 0.2504064f, 0.0f, 0, 3000); return NULL; }
sequence *start_gutted_stinger() { mus[GUTTED_STINGER] = audio_sample_start("EP01 Gutted Stinger", 0, 0.177706f); return NULL; }
sequence *start_lee_line() { mus[LEE_LINE] = audio_sample_start("EP02 Leeline", 0, 0.07848254f); return NULL; }
sequence *start_atmo_ext_house() { mus[ATMO_EXT_HOUSE] = audio_sample_start("EP02 Atmo Ext House", 0, 1.0f); return NULL; }
sequence *fade_matt_escape() { audio_sample_fade(mus[MATT_ESCAPE], 0.1586634f, 0.0f, 500, 7000); return NULL; }
sequence *fade_lee_line() { audio_sample_fade(mus[LEE_LINE], 0.07848254f, 0.06439577f, 16833, 18875); return NULL; }
sequence *stop_matt_escape() { audio_sample_stop_and_free(mus[MATT_ESCAPE]); return NULL; }
sequence *maybe_start_matt_escape() { if (!game_vars.matt_escape) { mus[MATT_ESCAPE] = audio_sample_start("EP01 Matt Escape", 0, 0.1586634f); } game_vars.matt_escape = 0; return NULL; }
sequence *start_atmo_train_station() { mus[ATMO_TRAIN_STATION] = audio_sample_start("EP02 Atmo Ext Train Station", 1, 1.0f); return NULL; }
sequence *start_atmo_train() { mus[ATMO_TRAIN] = audio_sample_start("EP02 Atmo Ext Train", 0, 1.0f); return NULL; }
sequence *fade_matt_escape2() { audio_sample_set_volume(mus[MATT_ESCAPE], 0.1098583f); return NULL; }
sequence *fade_matt_escape3() { audio_sample_set_volume(mus[MATT_ESCAPE], 0.2363281f); return NULL; }
sequence *fade_matt_escape4() { audio_sample_fade(mus[MATT_ESCAPE], 0.1098583f, 0.0f, 7667, 11667); return NULL; }
sequence *fade_matt_escape5() { audio_sample_fade(mus[MATT_ESCAPE], 0.1098583f, 0.0f, 0, 4000); return NULL; }
sequence *fade_lee_line2() { audio_sample_fade(mus[LEE_LINE], 0.06439577f, 0.09268466f, 500, 2000); return NULL; }
sequence *fade_lee_line3() { audio_sample_fade(mus[LEE_LINE], 0.06439577f, 0.0f, 0, 20000); return NULL; }
sequence *stop_atmo_ext_house() { audio_sample_stop_and_free(mus[ATMO_EXT_HOUSE]); return NULL; }
sequence *start_showdown_riser() { mus[SHOWDOWN_RISER] = audio_sample_start("EP11 Showdown Riser", 0, 0.1749866f); return NULL; }
sequence *stop_atmo_train_station() { audio_sample_stop_and_free(mus[ATMO_TRAIN_STATION]); return NULL; }
sequence *start_jeff_line() { mus[JEFF_LINE] = audio_sample_start("EP02 Jeffline", 0, 0.04032431f); return NULL; }
sequence *fade_jeff_line() { audio_sample_fade(mus[JEFF_LINE], 0.04032431f, 0.0750012f, 36375, 48375); return NULL; }
sequence *fade_jeff_line2() { audio_sample_fade(mus[JEFF_LINE], 0.04032431f, 0.09360203f, 20875, 24375); return NULL; }
sequence *start_jeff_gun() { mus[JEFF_GUN] = audio_sample_start("EP02 Jeffgun", 0, 0.2502597f); return NULL; }
sequence *start_leg_it() { mus[LEG_IT] = audio_sample_start("EP02 Leg it", 0, 0.2508919f); return NULL; }
sequence *start_atmo_house() { mus[ATMO_HOUSE] = audio_sample_start("EP02 Atmo Int House", 1, 1.0f); return NULL; }
sequence *start_any_suggestions() { mus[ANY_SUGGESTIONS] = audio_sample_start("EP02 Any Suggestions", 0, 0.2505929f); return NULL; }
sequence *start_one_less_problem() { mus[ONE_LESS_PROBLEM] = audio_sample_start("EP02 One Less Problem", 0, 0.2497907f); return NULL; }
sequence *fade_any_suggestions() { audio_sample_fade(mus[ANY_SUGGESTIONS], 0.2505929f, 0.0f, 7167, 8167); return NULL; }
sequence *stop_any_suggestions() { audio_sample_stop_and_free(mus[ANY_SUGGESTIONS]); return NULL; }
sequence *fade_any_suggestions2() { audio_sample_fade(mus[ANY_SUGGESTIONS], 0.2505929f, 0.0f, 3417, 12400); return NULL; }
sequence *start_pushing() { mus[PUSHING_YOUR_CHANCE] = audio_sample_start("EP02 Pushing your chance", 0, 0.2500465f); return NULL; }
sequence *fade_one_less_problem() { audio_sample_fade(mus[ONE_LESS_PROBLEM], 0.2497907f, 0.0f, 16000, 20000); return NULL; }
sequence *stop_one_less_problem() { audio_sample_stop_and_free(mus[ONE_LESS_PROBLEM]); return NULL; }
sequence *fade_one_less_problem2() { audio_sample_fade(mus[ONE_LESS_PROBLEM], 0.2497907f, 0.0f, 16292, 20292); return NULL; }
sequence *start_lets_go() { mus[LETS_GO] = audio_sample_start("EP02 Let's go", 0, 0.0234771f); return NULL; }
sequence *stop_pushing() { audio_sample_stop_and_free(mus[PUSHING_YOUR_CHANCE]); return NULL; }
sequence *fade_lets_go() { audio_sample_set_volume(mus[LETS_GO], 0.09779948f); return NULL; }
sequence *stop_atmo_house() { audio_sample_stop_and_free(mus[ATMO_HOUSE]); return NULL; }
sequence *stop_lee_line() { audio_sample_stop_and_free(mus[LEE_LINE]); return NULL; }
sequence *fade_pushing() { audio_sample_fade(mus[PUSHING_YOUR_CHANCE], 0.2500465f, 0.0f, 10292, 19292); return NULL; }
sequence *start_lets_go2() { mus[LETS_GO] = audio_sample_start("EP02 Let's go", 0, 0.02562345f); return NULL; }
sequence *fade_lets_go2() { audio_sample_fade(mus[LETS_GO], 0.02562345f, 0.09779948f, 10292, 19292); return NULL; }
sequence *start_dance() { mus[DANCE_CHERRY_BLOSSOMS] = audio_sample_start("EP03 Dance of the Cherry Blossoms", 1, 0.0f); return NULL; }
sequence *start_atmo_entrance() { mus[ATMO_ENTRANCE] = audio_sample_start("EP03 Atmo Ext Entrance", 1, 1.0f); return NULL; }
sequence *start_auction_guy() { mus[AUCTION_GUY] = audio_sample_start("EP07 Auction Guy", 0, 0.09981957f); return NULL; }
sequence *fade_lets_go3() { audio_sample_set_volume(mus[LETS_GO], 0.07045589f); return NULL; }
sequence *fade_lets_go4() { audio_sample_fade(mus[LETS_GO], 0.07045589f, 0.1091634f, 17000, 18000); return NULL; }
sequence *fade_dance() { audio_sample_fade(mus[DANCE_CHERRY_BLOSSOMS], 0.0f, 0.1775957f, 73958, 79958); return NULL; }
sequence *start_matt_vo() { if (game_vars.respect_earned) { mus[VO_MATT_NO_MONEY] = audio_voice_sample_start("EP03 VO Matt No Money Taken", 0, 1.0f); } else { mus[VO_MATT_MONEY] = audio_voice_sample_start("EP03 VO Matt Money Taken", 0, 1.0f); } return NULL; }
sequence *stop_auction_guy() { audio_sample_stop_and_free(mus[AUCTION_GUY]); return NULL; }
sequence *stop_atmo_entrance() { audio_sample_stop_and_free(mus[ATMO_ENTRANCE]); return NULL; }
sequence *change_dance() { audio_sample_set_volume(mus[DANCE_CHERRY_BLOSSOMS], 0.1420184f); return NULL; }
sequence *start_atmo_auction() { mus[ATMO_AUCTION] = audio_sample_start("EP03 Atmo Int Auction", 1, 1.0f); return NULL; }
sequence *change_dance2() { audio_sample_set_volume(mus[DANCE_CHERRY_BLOSSOMS], 0.07851835f); return NULL; }
sequence *start_taking_seats() { mus[TAKING_SEATS] = audio_sample_start("EP03 Taking Seats", 0, 0.1574344f); return NULL; }
sequence *stop_taking_seats() { audio_sample_stop_and_free(mus[TAKING_SEATS]); return NULL; }
sequence *stop_dance() { audio_sample_stop_and_free(mus[DANCE_CHERRY_BLOSSOMS]); return NULL; }
sequence *fade_taking_seats() { audio_sample_fade(mus[TAKING_SEATS], 0.1574344f, 0.0f, 69083, 79083); return NULL; }
sequence *start_bowl_auction() { mus[BOWL_AUCTION] = audio_sample_start("EP03 Bowl Auction", 0, 0.1023089f); return NULL; }
sequence *fade_bowl_auction() { audio_sample_fade(mus[BOWL_AUCTION], 0.1023089f, 0.1303438f, 90917, 92917); return NULL; }
sequence *fade_bidding_flache() { audio_sample_fade(mus[BIDDING_FLACHE], 0.422129f, 0.2513284f, 158625, 160625); return NULL; }
sequence *start_bidding_flache() { mus[BIDDING_FLACHE] = audio_sample_start("EP03 Bidding Flache Nu", 0, 0.422129f); return NULL; }
sequence *start_bidding_riser_1() { mus[BIDDING_RISER_INTERVENE_1] = audio_sample_start("EP03 Bidding Riser Intervene I", 0, 0.1186769f); return NULL; }
sequence *stop_atmo_auction() { audio_sample_stop_and_free(mus[ATMO_AUCTION]); return NULL; }
sequence *start_atmo_hall() { mus[ATMO_HALL] = audio_sample_start("EP03 Atmo Int Hall", 1, 1.0f); return NULL; }
sequence *stop_bidding_flache() { audio_sample_stop_and_free(mus[BIDDING_FLACHE]); return NULL; }
sequence *start_dance2() { mus[DANCE_CHERRY_BLOSSOMS] = audio_sample_start("EP03 Dance of the Cherry Blossoms", 0, 0.2655425f); return NULL; }
sequence *fade_bidding_riser_1() { audio_sample_fade(mus[BIDDING_RISER_INTERVENE_1], 0.1186769f, 0.0f, 39750, 45250); return NULL; }
sequence *stop_bidding_riser_1() { audio_sample_stop_and_free(mus[BIDDING_RISER_INTERVENE_1]); return NULL; }
sequence *start_bidding_riser_2() { mus[BIDDING_RISER_INTERVENE_2] = audio_sample_start("EP03 Bidding Riser Intervene II", 0, 0.09432838f); return NULL; }
sequence *start_bidding_riser_let_her() { mus[BIDDING_RISER_LET_HER] = audio_sample_start("EP03 Bidding Riser Let Her", 0, 0.1192486f); return NULL; }
sequence *stop_bidding_riser_let_her() { audio_sample_stop_and_free(mus[BIDDING_RISER_LET_HER]); return NULL; }
sequence *fade_bidding_riser_let_her() { audio_sample_fade(mus[BIDDING_RISER_LET_HER], 0.1192486f, 0.0f, 57912, 62250); return NULL; }
sequence *start_dance3() { mus[DANCE_CHERRY_BLOSSOMS] = audio_sample_start("EP03 Dance of the Cherry Blossoms", 0, 0.26361f); return NULL; }
sequence *fade_bidding_flache2() { audio_sample_fade(mus[BIDDING_FLACHE], 0.2513284f, 0.0f, 0, 5250); return NULL; }
sequence *fade_dance2() { audio_sample_fade(mus[DANCE_CHERRY_BLOSSOMS], 0.26361f, 0.0f, 6750, 10250); return NULL; }
sequence *start_car_park_elevator() { mus[CAR_PARK_ELEVATOR] = audio_sample_start("EP03 Carpark Elevator Edit", 0, 0.2932352f); return NULL; }
sequence *stop_atmo_hall() { audio_sample_stop_and_free(mus[ATMO_HALL]); return NULL; }
sequence *start_atmo_basement() { mus[ATMO_BASEMENT_GUARD] = audio_sample_start("EP03 Atmo Int Basement Guard", 1, 1.0f); return NULL; }
sequence *start_brutal_p1() { mus[BRUTAL_CONSEQUENCE_1] = audio_sample_start("EP03 Brutal Consequence Part I", 0, 0.07070678f); return NULL; }
sequence *fade_car_park_elevator() { audio_sample_fade(mus[CAR_PARK_ELEVATOR], 0.2932352f, 0.0f, 7500, 10500); return NULL; }
sequence *stop_car_park_elevator() { audio_sample_stop_and_free(mus[CAR_PARK_ELEVATOR]); return NULL; }
sequence *start_brutal_p1_2() { mus[BRUTAL_CONSEQUENCE_1] = audio_sample_start("EP03 Brutal Consequence Part I", 0, 0.07147954f); return NULL; }
sequence *fade_car_park_elevator2() { audio_sample_fade(mus[CAR_PARK_ELEVATOR], 0.2932352f, 0.0f, 6333, 9333); return NULL; }
sequence *start_dance4() { mus[DANCE_CHERRY_BLOSSOMS] = audio_sample_start("EP03 Dance of the Cherry Blossoms", 0, 0.2647797f); return NULL; }
sequence *fade_bidding_riser_2() { audio_sample_fade(mus[BIDDING_RISER_INTERVENE_2], 0.09432838f, 0.0f, 18833, 24833); return NULL; }
sequence *stop_bidding_riser_2() { audio_sample_stop_and_free(mus[BIDDING_RISER_INTERVENE_2]); return NULL; }
sequence *start_awareness_downlifter() { mus[AWARENESS_DOWNLIFTER] = audio_sample_start("EP03 Awareness Downlifter", 0, 0.1007423f); return NULL; }
sequence *start_awareness() { mus[AWARENESS] = audio_sample_start("EP03 Awareness", 0, 0.1590764f); return NULL; }
sequence *start_atmo_inside_office() { mus[ATMO_INSIDE_OFFICE] = audio_sample_start("EP03 Atmo Int Inside Office", 1, 1.0f); return NULL; }
sequence *start_atmo_outside_office() { mus[ATMO_OUTSIDE_OFFICE] = audio_sample_start("EP03 Atmo Int Outside Office", 1, 1.0f); return NULL; }
sequence *fade_car_park_elevator3() { audio_sample_fade(mus[CAR_PARK_ELEVATOR], 0.2932352f, 0.0f, 16000, 19000); return NULL; }
sequence *stop_atmo_inside_office() { audio_sample_stop_and_free(mus[ATMO_INSIDE_OFFICE]); return NULL; }
sequence *stop_awareness() { audio_sample_stop_and_free(mus[AWARENESS]); return NULL; }
sequence *fade_awareness() { audio_sample_fade(mus[AWARENESS], 0.1590764f, 0.0f, 5083, 6792); return NULL; }
sequence *start_hainsworth_office() { mus[HAINSWORTH_OFFICE] = audio_sample_start("EP03 Hainsworth Office", 0, 0.03639143f); return NULL; }
sequence *fade_hainsworth_office() { audio_sample_fade(mus[HAINSWORTH_OFFICE], 0.03639143f, 0.1003858f, 10333, 20333); return NULL; }
sequence *fade_hainsworth_office2() { audio_sample_fade(mus[HAINSWORTH_OFFICE], 0.03639143f, 0.1005293f, 13125, 21000); return NULL; }
sequence *start_hainsworth_elevator() { mus[HAIMSWORTH_ELEVATOR] = audio_sample_start("EP03 Haimsworth Elevator", 0, 0.1580438f); return NULL; }
sequence *stop_hainsworth_office() { audio_sample_stop_and_free(mus[HAINSWORTH_OFFICE]); return NULL; }
sequence *fade_hainsworth_office3() { audio_sample_fade(mus[HAINSWORTH_OFFICE], 0.1005293f, 0.0f, 12583, 14500); return NULL; }
sequence *start_get_away_long() { mus[GET_AWAY_LONG] = audio_sample_start("EP04 Get Away LONG", 0, 0.1569345f); return NULL; }	
sequence *maybe_start_get_away_long() { if (game_vars.passed_by_seg341) { mus[GET_AWAY_LONG] = audio_sample_start("EP04 Get Away LONG", 0, 0.1587854f); } return NULL; }	
sequence *start_brutal_riser() { mus[BRUTAL_RISER] = audio_sample_start("EP03 Brutal Riser", 0, 0.1490377f); return NULL; }
sequence *start_brutal_p1_3() { mus[BRUTAL_CONSEQUENCE_1] = audio_sample_start("EP03 Haimsworth Elevator", 0, 0.1248198f); return NULL; }
sequence *start_brutal_p2() { mus[BRUTAL_CONSEQUENCE_2] = audio_sample_start("EP03 Brutal Consequence Part II nu", 0, 0.2247357f); return NULL; }
sequence *start_brutal_p3() { mus[BRUTAL_CONSEQUENCE_3] = audio_sample_start("EP03 Brutal Consequence Part III", 0, 0.1264629f); return NULL; }
sequence *start_awareness_downlifter2() { mus[AWARENESS_DOWNLIFTER] = audio_sample_start("EP03 Awareness Downlifter", 0, 0.1807707f); return NULL; }
sequence *start_freight() { mus[ATMO_FREIGHT_LIFT_PING] = audio_sample_start("EP03 Atmo Int Freight Lift Ping", 0, 0.5029765f); return NULL; }
sequence *start_alarm() { mus[ATMO_ALARM] = audio_sample_start("EP03 Atmo Int Alarm", 0, 1.0f); return NULL; }
sequence *start_alarm2() { mus[ATMO_ALARM] = audio_sample_start("EP03 Atmo Int Alarm", 1, 1.0f); return NULL; }
sequence *start_hainsworth_lobby() { mus[HAINSWORTH_LOBBY] = audio_sample_start("EP03 Hainsworth Lobby", 0, 0.2504249f); return NULL; }
sequence *start_hainsworth_lobby2() { mus[HAINSWORTH_LOBBY] = audio_sample_start("EP03 Hainsworth Lobby", 0, 0.2511927f); return NULL; }
sequence *start_atmo_basement_sebastien() { mus[ATMO_BASEMENT_SEBASTIEN] = audio_sample_start("EP03 Atmo Int Basement Sebastien", 1, 1.0f); return NULL; }
sequence *fade_brutal_p1() { audio_sample_fade(mus[BRUTAL_CONSEQUENCE_1], 0.1248198f, 0.0f, 33875, 37000); return NULL; }
sequence *fade_brutal_p2() { audio_sample_fade(mus[BRUTAL_CONSEQUENCE_2], 0.2247357f, 0.1576557f, 52792, 60792); return NULL; }
sequence *fade_brutal_p2_2() { audio_sample_fade(mus[BRUTAL_CONSEQUENCE_2], 0.1576557f, 0.1587639f, 542, 2542); return NULL; }
sequence *fade_brutal_p2_3() { audio_sample_fade(mus[BRUTAL_CONSEQUENCE_2], 0.1587639f, 0.2004773f, 4750, 6750); return NULL; }
sequence *fade_brutal_p2_4() { audio_sample_fade(mus[BRUTAL_CONSEQUENCE_2], 0.2004773f, 0.0f, 30250, 35250); return NULL; }
sequence *fade_brutal_p3() { audio_sample_fade(mus[BRUTAL_CONSEQUENCE_3], 0.1264629f, 0.0f, 292, 7250); return NULL; }
sequence *fade_alarm() { audio_sample_fade(mus[ATMO_ALARM], 1.0f, 0.0f, 38167, 42792); return NULL; }
sequence *stop_brutal_p1() { audio_sample_stop_and_free(mus[BRUTAL_CONSEQUENCE_1]); return NULL; }
sequence *stop_brutal_p3() { audio_sample_stop_and_free(mus[BRUTAL_CONSEQUENCE_3]); return NULL; }
sequence *stop_atmo_basement_guard() { audio_sample_stop_and_free(mus[ATMO_BASEMENT_GUARD]); return NULL; }
sequence *stop_alarm() { audio_sample_stop_and_free(mus[ATMO_ALARM]); return NULL; }
sequence *stop_hainsworth_elevator() { audio_sample_stop_and_free(mus[HAIMSWORTH_ELEVATOR]); return NULL; }
sequence *stop_atmo_basement_sebastien() { audio_sample_stop_and_free(mus[ATMO_BASEMENT_SEBASTIEN]); return NULL; }
sequence *maybe_start_get_away_riser() { if (game_vars.passed_by_seg341) { mus[GET_AWAY_RISER] = audio_sample_start("EP03 Get Away Riser", 0, 0.3176751f); } return NULL;}
sequence *fade_multiple() { audio_sample_fade(mus[AWARENESS], 0.1590764f, 0.0f, 9625, 13167); audio_sample_fade(mus[HAIMSWORTH_ELEVATOR], 0.1580438f, 0.0f, 9625, 13167); return NULL; }
sequence *stop_hainsworth_stairs() { audio_sample_stop_and_free(mus[HAIMSWORTH_STAIRS]); return NULL; }
sequence *stop_atmo_outside_office() { audio_sample_stop_and_free(mus[ATMO_OUTSIDE_OFFICE]); return NULL; }
sequence *stop_brutal_p2() { audio_sample_stop_and_free(mus[BRUTAL_CONSEQUENCE_2]); return NULL; }
sequence *stop_brutal_keypad() { audio_sample_stop_and_free(mus[BRUTAL_CONSEQUENCE_KEYPAD]); return NULL; }
sequence *fade_hainsworth_office4() { audio_sample_fade(mus[HAINSWORTH_OFFICE], 0.1005293f, 0.0f, 17625, 20000); return NULL; }
sequence *fade_hainsworth_office5() { audio_sample_fade(mus[HAINSWORTH_OFFICE], 0.1005293f, 0.100406f, 8625, 18625); return NULL; }
sequence *fade_brutal_p1_2() { audio_sample_fade(mus[BRUTAL_CONSEQUENCE_1], 0.1248198f, 0.124516f, 21208, 25458); return NULL; }
sequence *fade_brutal_p1_3() { audio_sample_fade(mus[BRUTAL_CONSEQUENCE_1], 0.124516f, 0.0f, 34875, 42583); return NULL; }
sequence *fade_awareness2() { audio_sample_fade(mus[AWARENESS], 0.1590764f, 0.0f, 3000, 6000); return NULL; }
sequence *start_hainsworth_lobby3() { mus[HAINSWORTH_LOBBY] = audio_sample_start("EP03 Hainsworth Lobby", 0, 0.2511107f); return NULL; }
sequence *start_hainsworth_elevator2() { mus[HAIMSWORTH_ELEVATOR] = audio_sample_start("EP03 Haimsworth Elevator", 0, 0.1577016f); return NULL; }
sequence *start_awareness_downlifter3() { mus[AWARENESS_DOWNLIFTER] = audio_sample_start("EP03 Awareness Downlifter", 0, 0.1806578f); return NULL; }
sequence *start_freight2() { mus[ATMO_FREIGHT_LIFT_PING] = audio_sample_start("EP03 Atmo Int Freight Lift Ping", 0, 0.503014f); return NULL; }
sequence *start_brutal_p2_2() { mus[BRUTAL_CONSEQUENCE_2] = audio_sample_start("EP03 Brutal Consequence Part II nu", 0, 0.222277f); return NULL; }
sequence *start_brutal_keypad() { mus[BRUTAL_CONSEQUENCE_KEYPAD] = audio_sample_start("EP03 Brutal Consequence Keypad", 0, 0.2525122f); return NULL; }
sequence *start_brutal_keypad2() { mus[BRUTAL_CONSEQUENCE_KEYPAD] = audio_sample_start("EP03 Brutal Consequence Keypad", 0, 0.09980504f); return NULL; }
sequence *start_hainsworth_stairs() { mus[HAIMSWORTH_STAIRS] = audio_sample_start("EP03 Haimsworth Stairs", 0, 0.1253717f); return NULL; }
sequence *start_get_away_long2() { mus[GET_AWAY_LONG] = audio_sample_start("EP04 Get Away LONG", 0, 0.1575244f); return NULL; }
sequence *fade_brutal_p2_5() { audio_sample_fade(mus[BRUTAL_CONSEQUENCE_2], 0.1576557f, 0.0f, 13500, 22500); return NULL; }
sequence *fade_brutal_p2_6() { audio_sample_fade(mus[BRUTAL_CONSEQUENCE_2], 0.1576557f, 0.07212745f, 7000, 8000); return NULL; }
sequence *fade_brutal_p2_7() { audio_sample_fade(mus[BRUTAL_CONSEQUENCE_2], 0.07212745f, 0.0f, 16667, 25667); return NULL; }
sequence *fade_brutal_p2_8() { audio_sample_fade(mus[BRUTAL_CONSEQUENCE_2], 0.1576557f, 0.1229217f, 83, 3083); return NULL; }
sequence *fade_brutal_p2_9() { audio_sample_fade(mus[BRUTAL_CONSEQUENCE_2], 0.1229217f, 0.0f, 9375, 17833); return NULL; }
sequence *maybe_start_hainsworth_elevator() { if (game_vars.passed_by_seg326) { mus[HAIMSWORTH_ELEVATOR] = audio_sample_start("EP03 Haimsworth Elevator", 0, 0.1581205f); } return NULL; }
sequence *fade_bmw_m5() { audio_sample_fade(mus[ATMO_BMW_M5], 1.0f, 0.0f, 0, 2000); return NULL; }
sequence *start_get_away_short() { mus[GET_AWAY_SHORT] = audio_sample_start("EP04 Get Away SHORT", 0, 0.1576156f); return NULL; }
sequence *start_siren() { mus[ATMO_SIREN] = audio_sample_start("EP04 Atmo Ext Siren 1", 0, 0.503346f); return NULL; }
sequence *start_bmw_i8() { mus[ATMO_BMW_I8] = audio_sample_start("EP04 Atmo Int BMW i8", 1, 1.0f); return NULL; }
sequence *start_bmw_m5() { mus[ATMO_BMW_M5] = audio_sample_start("EP04 Atmo Int BMW M5", 1, 1.0f); return NULL; }
sequence *stop_bmw_m5() { audio_sample_stop_and_free(mus[ATMO_BMW_M5]); return NULL; }
sequence *change_get_away_short() { audio_sample_set_volume(mus[GET_AWAY_SHORT], 0.1126353f); return NULL; }
sequence *change_get_away_short2() { audio_sample_set_volume(mus[GET_AWAY_SHORT], 0.1543445f); return NULL; }
sequence *change_get_away_short3() { audio_sample_set_volume(mus[GET_AWAY_SHORT], 0.1130907f); return NULL; }
sequence *change_get_away_short4() { audio_sample_set_volume(mus[GET_AWAY_SHORT], 0.1561145f); return NULL; }
sequence *change_get_away_short5() { audio_sample_set_volume(mus[GET_AWAY_SHORT], 0.1112274f); return NULL; }
sequence *change_get_away_short6() { audio_sample_set_volume(mus[GET_AWAY_SHORT], 0.1568132f); return NULL; }
sequence *maybe_start_get_away_long2() { if (!game_vars.get_away_long_playing) { mus[GET_AWAY_LONG] = audio_sample_start("EP04 Get Away LONG", 0, 0.1588651f); } return NULL; }
sequence *change_get_away_long() { audio_sample_set_volume(mus[GET_AWAY_LONG], 0.1109945f); return NULL; }
sequence *change_get_away_long2() { audio_sample_set_volume(mus[GET_AWAY_LONG], 0.1564935f); return NULL; }
sequence *change_get_away_long3() { audio_sample_set_volume(mus[GET_AWAY_LONG], 0.1120107f); return NULL; }
sequence *change_get_away_long4() { audio_sample_set_volume(mus[GET_AWAY_LONG], 0.1581767f); return NULL; }
sequence *fade_siren_p3() { audio_sample_fade(mus[ATMO_SIREN_3], 1.0f, 0.0f, 4125, 18125); return NULL; }
sequence *fade_siren() { audio_sample_fade(mus[ATMO_SIREN], 1.0f, 0.1783854f, 8792, 14400); return NULL; }
sequence *fade_siren2() { audio_sample_fade(mus[ATMO_SIREN], 0.1783854f, 0.4423451f, 16167, 18667); return NULL; }
sequence *fade_get_away_long() { audio_sample_fade(mus[GET_AWAY_LONG], 0.08918454f, 0.0f, 2375, 4375); return NULL; }
sequence *fade_after_crash() { audio_sample_fade(mus[AFTER_CRASH], 0.06961862f, 0.09751472f, 105833, 115833); return NULL; }
sequence *start_ford_transit() { mus[ATMO_FORD_TRANSIT] = audio_sample_start("EP04 Atmo Int Ford Transit", 1, 1.0f); return NULL; }
sequence *start_fire() { mus[ATMO_FIRE] = audio_sample_start("EP04 Atmo Ext Fire", 0, 1.0f); return NULL; }
sequence *start_atmo_london() { mus[ATMO_LONDON] = audio_sample_start("EP04 Atmo Ext London", 1, 1.0f); return NULL; }
sequence *start_get_away_riser_new() { mus[GET_AWAY_RISER_NEW] = audio_sample_start("EP04 Get Away Riser NEU", 0, 0.2519232f); return NULL; }
sequence *start_after_crash() { mus[AFTER_CRASH] = audio_sample_start("EP04 After Crash NEU", 0, 0.06961862f); return NULL; }
sequence *stop_bmw_i8() { audio_sample_stop_and_free(mus[ATMO_BMW_I8]); return NULL; }
sequence *stop_get_away_short() { audio_sample_stop_and_free(mus[GET_AWAY_SHORT]); return NULL; }
sequence *stop_get_away_long() { audio_sample_stop_and_free(mus[GET_AWAY_LONG]); return NULL; }
sequence *stop_get_away_riser_new() { audio_sample_stop_and_free(mus[GET_AWAY_RISER_NEW]); return NULL; }
sequence *stop_ford_transit() { audio_sample_stop_and_free(mus[ATMO_FORD_TRANSIT]); return NULL; }
sequence *change_get_away_short7() { audio_sample_set_volume(mus[GET_AWAY_SHORT], 0.08882134f); return NULL; }
sequence *change_get_away_long5() { audio_sample_set_volume(mus[GET_AWAY_LONG], 0.08918454f); return NULL; }
sequence *start_siren2() { mus[ATMO_SIREN] = audio_sample_start("EP04 Atmo Ext Siren 1", 0, 1.0f); return NULL; }
sequence *start_siren_p2() { mus[ATMO_SIREN_2] = audio_sample_start("EP04 Atmo Ext Siren 2", 0, 1.0f); return NULL; }
sequence *start_siren_p3() { mus[ATMO_SIREN_3] = audio_sample_start("EP04 Atmo Ext Siren 3", 0, 1.0f); return NULL; }
sequence *stop_siren() { audio_sample_stop_and_free(mus[ATMO_SIREN]); return NULL; }
sequence *stop_siren_p3() { audio_sample_stop_and_free(mus[ATMO_SIREN_3]); return NULL; }
sequence *stop_atmo_london() { audio_sample_stop_and_free(mus[ATMO_LONDON]); return NULL; }
sequence *stop_fire() { audio_sample_stop_and_free(mus[ATMO_FIRE]); return NULL; }
sequence *fade_police_everywhere() { audio_sample_fade(mus[POLICE_EVERYWHERE], 0.158687f, 0.1111572f, 0, 6000); return NULL; }
sequence *fade_police_everywhere2() { audio_sample_fade(mus[POLICE_EVERYWHERE], 0.1111572f, 0.1594517f, 46750, 52750); return NULL; }
sequence *fade_police_everywhere3() { audio_sample_fade(mus[POLICE_EVERYWHERE], 0.1594517f, 0.0f, 708, 4542); return NULL; }
sequence *fade_police_everywhere4() { audio_sample_fade(mus[POLICE_EVERYWHERE], 0.1594517f, 0.0f, 0, 5167); return NULL; }
sequence *fade_woe_dark_end() { audio_sample_fade(mus[WOE_DARK_END], 0.0796349f, 0.1242747f, 20000, 23000); return NULL; }
sequence *fade_woe_dark() { audio_sample_fade(mus[WOE_DARK], 0.07858334f, 0.0f, 0, 4000); return NULL; }
sequence *fade_woe_bowl_music2() { audio_sample_fade(mus[AFTER_CRASH], 0.07961292f, 0.0f, 0, 4000); return NULL; }
sequence *fade_after_crash2() { audio_sample_fade(mus[AFTER_CRASH], 0.09751472f, 0.0f, 2167, 8833); return NULL; }
sequence *fade_woe_bowl_music() { audio_sample_fade(mus[WOE_BOWL_MUSIC], 0.07952181f, 0.07961292f, 28208, 33208); return NULL; }
sequence *start_police_everywhere() { mus[POLICE_EVERYWHERE] = audio_sample_start("Ep05A PoliceEverywhere 3x", 0, 0.158687f); game_vars.police_everywhere_playing = 1; return NULL; }
sequence *start_hong_kong_backdoor() { mus[ATMO_HONG_KONG_BACK_DOOR] = audio_sample_start("EP05A Atmo Ext Hong Kong City Back Door", 1, 1.0f); return NULL; }
sequence *start_woe_dark() { mus[WOE_DARK] = audio_sample_start("EP05A MrWoe Woe Dark", 0, 0.07858334f); return NULL; }
sequence *start_push_your_chances() { mus[PUSHING_YOUR_CHANCES] = audio_sample_start("EP05A Pushing your chances", 0, 0.1241259f); return NULL; }
sequence *start_woe_office() { mus[ATMO_WOE_OFFICE] = audio_sample_start("EP05A Atmo Int Woe Office", 1, 1.0f); return NULL; }
sequence *start_woe_dark_end() { mus[WOE_DARK_END] = audio_sample_start("EP05A MrWoe Woe Dark End", 0, 0.0796349f); return NULL; }
sequence *start_woes_resto() { mus[WOES_RESTO] = audio_sample_start("EP05A WoesResto", 0, 0.0f); return NULL; }
sequence *start_woe_bowl_music() { mus[WOE_BOWL_MUSIC] = audio_sample_start("EP05A MrWoe Bowlmusic", 0, 0.07952181f); return NULL; }
sequence *start_atmo_hong_kong() { mus[ATMO_HONG_KONG_CITY] = audio_sample_start("EP05A Atmo Int Hong Kong City", 1, 1.0f); return NULL; }
sequence *stop_after_crash() { audio_sample_stop_and_free(mus[AFTER_CRASH]); return NULL; }
sequence *stop_atmo_hong_kong() { audio_sample_stop_and_free(mus[ATMO_HONG_KONG_CITY]); return NULL; }
sequence *stop_woes_resto() { audio_sample_stop_and_free(mus[WOES_RESTO]); return NULL; }
sequence *stop_woe_bowl_music() { audio_sample_stop_and_free(mus[WOE_BOWL_MUSIC]); return NULL; }
sequence *stop_woe_dark() { audio_sample_stop_and_free(mus[WOE_DARK]); return NULL; }
sequence *stop_woe_office() { audio_sample_stop_and_free(mus[ATMO_WOE_OFFICE]); return NULL; }
sequence *stop_police_everywhere() { audio_sample_stop_and_free(mus[POLICE_EVERYWHERE]); return NULL; }
sequence *stop_hong_kong_backdoor() { audio_sample_stop_and_free(mus[ATMO_HONG_KONG_BACK_DOOR]); return NULL; }
sequence *change_woes_resto() { audio_sample_set_volume(mus[WOES_RESTO], 0.09954205f); return NULL; }
sequence *maybe_start_police_everywhere() { if (!game_vars.police_everywhere_playing) { mus[POLICE_EVERYWHERE] = audio_sample_start("Ep05A PoliceEverywhere 3x", 0, 0.249946f); } game_vars.police_everywhere_playing = 0; return NULL; }
sequence *start_atmo_police_station() { mus[ATMO_POLICE_STATION] = audio_sample_start("EP05B Atmo Int Police Station", 1, 1.0f); return NULL; }
sequence *start_showdown_and_violence() { mus[SHOWDOWN_AND_VIOLENCE] = audio_sample_start("EP05B ShowdownAndViolence", 0, 0.3166535f); return NULL; }
sequence *start_tenseness() { mus[TENSENESS] = audio_sample_start("EP05B Tenseness", 0, 0.2510983f); return NULL; }
sequence *fade_police_everywhere5() { audio_sample_fade(mus[POLICE_EVERYWHERE], 0.249946f, 0.1590833f, 0, 3500); return NULL; }
sequence *fade_police_everywhere6() { audio_sample_fade(mus[POLICE_EVERYWHERE], 0.1590833f, 0.0f, 12333, 21333); return NULL; }
sequence *fade_tenseness() { audio_sample_fade(mus[TENSENESS], 0.2510983f, 0.0f, 49208, 50708); return NULL; }
sequence *stop_atmo_police_station() { audio_sample_stop_and_free(mus[ATMO_POLICE_STATION]); return NULL; }
sequence *stop_tenseness() { audio_sample_stop_and_free(mus[TENSENESS]); return NULL; }
sequence *fade_after_crash3() { audio_sample_fade(mus[AFTER_CRASH], 0.09751472f, 0.0f, 0, 6000); return NULL; }
sequence *start_radioplay() { mus[RADIO_PLAY] = audio_sample_start("EP06B Radioplay", 1, 1.0f); return NULL; }
sequence *stop_showdown_and_violence() { audio_sample_stop_and_free(mus[SHOWDOWN_AND_VIOLENCE]); return NULL; }
sequence *fade_hotel_romance2() { audio_sample_fade(mus[HOTEL_ROMANCE], 0.08464747f, 0.0f, 28333, 35958); return NULL; }
sequence *fade_hotel_romance() { audio_sample_fade(mus[HOTEL_ROMANCE], 0.09851323f, 0.08464747f, 6083, 14083); return NULL; }
sequence *fade_on_the_news() { audio_sample_fade(mus[ON_THE_NEWS], 0.09919386f, 0.0f, 0, 6750); return NULL; }
sequence *fade_pushing_your_chances() { audio_sample_fade(mus[PUSHING_YOUR_CHANCES], 0.1241259f, 0.06466196f, 0, 11000); return NULL; }
sequence *start_atmo_hotel_room() { mus[ATMO_HOTEL_ROOM] = audio_sample_start("EP06A Atmo Int Hotel Room", 1, 1.0f); return NULL; }
sequence *start_atmo_tv_bg_p1() { mus[ATMO_TV_BG_PART1] = audio_sample_start("EP06A Atmo Int TV Background Part 1", 0, 1.0f); return NULL; }
sequence *start_atmo_tv_bg_p2() { mus[ATMO_TV_BG_PART2] = audio_sample_start("EP06A Atmo Int TV Background Part 2", 0, 1.0f); return NULL; }
sequence *start_atmo_tv_bg_trans() { mus[ATMO_TV_BG_TRANS] = audio_sample_start("EP06A Atmo Int TV Background Transition", 0, 1.0f); return NULL; }
sequence *start_hotel_romance() { mus[HOTEL_ROMANCE] = audio_sample_start("EP06A Hotel Romance", 0, 0.09851323f); return NULL; }
sequence *start_on_the_news() { mus[ON_THE_NEWS] = audio_sample_start("EP06A On the News", 0, 0.09919386f); return NULL; }
sequence *start_on_the_news2() { mus[ON_THE_NEWS] = audio_sample_start("EP06A On the News", 0, 0.0973212f); return NULL; }
sequence *start_atmo_tv_bg_p3() { mus[ATMO_TV_BG_PART3] = audio_sample_start("EP06A Atmo Int TV Background Part 3", 0, 1.0f); return NULL; }
sequence *stop_hotel_romance() { audio_sample_stop_and_free(mus[HOTEL_ROMANCE]); return NULL; }
sequence *stop_atmo_tv_bg_trans() { audio_sample_stop_and_free(mus[ATMO_TV_BG_TRANS]); return NULL; }
sequence *stop_on_the_news() { audio_sample_stop_and_free(mus[ON_THE_NEWS]); return NULL; }
sequence *stop_atmo_hotel_room() { audio_sample_stop_and_free(mus[ATMO_HOTEL_ROOM]); return NULL; }
sequence *stop_atmo_stairway() { audio_sample_stop_and_free(mus[ATMO_STAIRWAY]); return NULL; }
sequence *start_tschoi_action() { mus[TSCHOI_ACTION] = audio_sample_start("EP06A Tschoi Action", 0, 0.1002888f); return NULL; }
sequence *fade_tschoi_action() { audio_sample_fade(mus[TSCHOI_ACTION], 0.1002888f, 0.126724f, 13833, 16167); return NULL; }
sequence *start_atmo_stairway() { mus[ATMO_STAIRWAY] = audio_sample_start("EP06A Atmo Int Stairway", 1, 1.0f); return NULL; }
sequence *start_atmo_backyard() { mus[ATMO_BACKYARD] = audio_sample_start("EP06A Atmo Ext Back yard", 1, 1.0f); return NULL; }
sequence *start_tschoi_stab() { mus[TSCHOI_STAB] = audio_sample_start("EP06A Tschoi Action STAB", 0, 0.2509432f); return NULL; }
sequence *stop_tschoi_action() { audio_sample_stop_and_free(mus[TSCHOI_ACTION]); return NULL; }
sequence *stop_atmo_backyard() { audio_sample_stop_and_free(mus[ATMO_BACKYARD]); return NULL; }
sequence *start_radioplay2() { mus[RADIO_PLAY] = audio_sample_start("EP06B Radioplay", 0, 0.0f); return NULL; }
sequence *fade_radioplay() { audio_sample_fade(mus[RADIO_PLAY], 0.0f, 1.0f, 3958, 5958); return NULL; }
sequence *stop_torture_end() { audio_sample_stop_and_free(mus[TORTURE_END]); return NULL; }
sequence *stop_tchoi_hotel() { audio_sample_stop_and_free(mus[TCHOI_HOTEL_ROOM]); return NULL; }
sequence *stop_thumbscrew_p2() { audio_sample_stop_and_free(mus[THUMBSCREW_P2]); return NULL; }
sequence *stop_short_knife() { audio_sample_stop_and_free(mus[SHORT_KNIFE]); return NULL; }
sequence *stop_long_knife() { audio_sample_stop_and_free(mus[LONG_KNIFE]); return NULL; }
sequence *stop_torture_main() { audio_sample_stop_and_free(mus[TORTURE_MAIN]); return NULL; }
sequence *stop_radioplay() { audio_sample_stop_and_free(mus[RADIO_PLAY]); return NULL; }
sequence *stop_thumbscrew_p1() { audio_sample_stop_and_free(mus[THUMBSCREW_P1]); return NULL; }
sequence *start_knife_accent_p1() { mus[KNIFE_ACCENT_P1] = audio_sample_start("EP06B Knife Accent I", 0, 0.1772321f); return NULL; }
sequence *start_knife_accent_p2() { mus[KNIFE_ACCENT_P2] = audio_sample_start("EP06B Knife Accent II", 0, 0.176941f); return NULL; }
sequence *start_atmo_radioplay() { mus[ATMO_RADIO_PLAY] = audio_sample_start("EP06B Atmo Int Radioplay", 0, 1.0f); return NULL; }
sequence *start_thumbscrew_p1() { mus[THUMBSCREW_P1] = audio_sample_start("EP06B Thumbscrew I", 0, 0.139111f); return NULL; }
sequence *start_tchoi_hotel() { mus[TCHOI_HOTEL_ROOM] = audio_sample_start("EP06B Atmo Int Tchoi Hotel Room", 0, 1.0f); return NULL; }
sequence *fade_radioplay2() { audio_sample_fade(mus[RADIO_PLAY], 0.2523407f, 0.0f, 15208, 18208); return NULL; }
sequence *maybe_start_radioplay() { if (!game_vars.radioplay_started) { mus[RADIO_PLAY] = audio_sample_start("EP06B Radioplay", 0, 0.2523407f); } return NULL; }
sequence *start_torture_main() { mus[TORTURE_MAIN] = audio_sample_start("EP06B Torture Main", 0, 0.141086f); return NULL; }
sequence *fade_thumbscrew_p1() { audio_sample_fade(mus[THUMBSCREW_P1], 0.139111f, 0.0f, 7125, 13500); return NULL; }
sequence *start_short_knife() { mus[SHORT_KNIFE] = audio_sample_start("EP06B Short Knife", 0, 0.177368f); return NULL; }
sequence *start_long_knife() { mus[LONG_KNIFE] = audio_sample_start("EP06B Long Knife", 0, 0.1412607f); return NULL; }
sequence *fade_torture_main() { audio_sample_fade(mus[TORTURE_MAIN], 0.141086f, 0.0f, 3583, 13583); return NULL; }
sequence *fade_torture_main2() { audio_sample_fade(mus[TORTURE_MAIN], 0.141086f, 0.0f, 1375, 11375); return NULL; }
sequence *fade_torture_main3() { audio_sample_fade(mus[TORTURE_MAIN], 0.141086f, 0.0f, 4917, 14917); return NULL; }
sequence *start_thumbscrew_talk() { mus[THUMBSCREW_TALK] = audio_sample_start("EP06B Thumbscrew Talk", 0, 0.1396351f); return NULL; }
sequence *fade_thumbscrew_p2() { audio_sample_fade(mus[THUMBSCREW_P2], 0.142008f, 0.0f, 0, 6000); return NULL; }
sequence *fade_thumbscrew_p2_2() { audio_sample_fade(mus[THUMBSCREW_P2], 0.142008f, 0.0f, 0, 5000); return NULL; }
sequence *start_torture_tom() { mus[TORTURE_TOM] = audio_sample_start("EP06B Torture Tom Hit", 0, 0.07788388f); return NULL; }
sequence *start_thumbscrew_p2() { mus[THUMBSCREW_P2] = audio_sample_start("EP06B Thumbscrew II", 0, 0.142008f); return NULL; }
sequence *start_thumbscrew_angry() { mus[THUMBSCREW_ANGRY] = audio_sample_start("EP06B Thumbscrew Angry", 0, 0.1417508f); return NULL; }
sequence *start_thumbscrew_angry2() { mus[THUMBSCREW_ANGRY] = audio_sample_start("EP06B Thumbscrew Angry", 0, 0.139737f); return NULL; }
sequence *start_torture_end() { mus[TORTURE_END] = audio_sample_start("EP06B Torture End", 0, 0.139868f); return NULL; }
sequence *start_matt_alone() { mus[MATT_ALONE] = audio_sample_start("EP07 Matt Alone", 0, 0.07865617f); return NULL; }
sequence *fade_matt_alone() { audio_sample_fade(mus[MATT_ALONE], 0.07865617f, 0.1126601f, 37542, 41000); return NULL; }
sequence *start_matt_alone2() { mus[MATT_ALONE] = audio_sample_start("EP07 Matt Alone", 0, 0.1120794f); return NULL; }
sequence *fade_torture_end() { audio_sample_fade(mus[TORTURE_END], 0.139868f, 0.0f, 33583, 39208); return NULL; }
sequence *fade_torture_end2() { audio_sample_fade(mus[TORTURE_END], 0.139868f, 0.1120614f, 333, 1333); return NULL; }
sequence *start_hoelzli_accent() { mus[HOELZLI_ACCENT] = audio_sample_start("EP06B Hoelzli Accent", 0, 0.177203f); return NULL; }
sequence *dont_know_trojan_jump() { if (!game_vars.know_trojan) return seg976(); return NULL; }
sequence *fade_matt_alone() { audio_sample_fade(mus[MATT_ALONE], 0.1114461f, 0.0f, 9167, 10750); return NULL; }
sequence *fade_auction_guy() { audio_sample_fade(mus[AUCTION_GUY], 0.1598199f, 0.0f, 4167, 8333); return NULL; }
sequence *fade_auction_guy2() { audio_sample_fade(mus[AUCTION_GUY], 0.1598199f, 0.0f, 0, 4000); return NULL; }
sequence *fade_auction_guy3() { audio_sample_fade(mus[AUCTION_GUY], 0.1598199f, 0.0f, 12042, 16042); return NULL; }	
sequence *fade_atmo_train_p5() { audio_sample_fade(mus[ATMO_TRAIN_5], 1.0f, 0.3167162f, 15250, 18250); return NULL; }	
sequence *fade_mayling_truth() { audio_sample_fade(mus[MAYLING_TRUTH], 0.1126381f, 0.0f, 18625, 24625); return NULL; }	
sequence *fade_drum_and_bass() { audio_sample_fade(mus[DRUM_AND_BASS], 0.0f, 0.2648638f, 60458, 69458); return NULL; }
sequence *fade_drum_and_bass2() { audio_sample_fade(mus[DRUM_AND_BASS], 0.0f, 0.2519945f, 53250, 60833); return NULL; }
sequence *fade_drum_and_bass3() { audio_sample_fade(mus[DRUM_AND_BASS], 0.2519945f, 0.0f, 0, 10958); return NULL; }
sequence *fade_drum_and_bass4() { audio_sample_fade(mus[DRUM_AND_BASS], 0.2519945f, 0.0f, 8250, 12292); return NULL; }
sequence *fade_drum_and_bass5() { audio_sample_fade(mus[DRUM_AND_BASS], 0.2519945f, 0.0f, 8167, 12167); return NULL; }
sequence *fade_drum_and_bass6() { audio_sample_fade(mus[DRUM_AND_BASS], 0.0f, 0.2513545f, 11667, 20667); return NULL; }
sequence *fade_drum_and_bass7() { audio_sample_fade(mus[DRUM_AND_BASS], 0.2519945f, 0.0f, 0, 12875); return NULL; }
sequence *fade_drum_and_bass8() { audio_sample_fade(mus[DRUM_AND_BASS], 0.2519945f, 0.0f, 26708, 31292); return NULL; }
sequence *fade_forged() { audio_sample_fade(mus[FORGED], 0.111812f, 0.0f, 14958, 21958); return NULL; }
sequence *fade_revellers_p5_2() { audio_sample_fade(mus[ATMO_REVELLERS_5], 0.5608469f, 0.0f, 14083, 21000); return NULL; }
sequence *fade_revellers_p5() { audio_sample_fade(mus[ATMO_REVELLERS_5], 0.5608469f, 0.0f, 16708, 23000); return NULL; }
sequence *stop_drum_and_bass() { audio_sample_stop_and_free(mus[DRUM_AND_BASS]); return NULL; }
sequence *stop_atmo_tunnel() { audio_sample_stop_and_free(mus[ATMO_TUNNEL]); return NULL; }
sequence *stop_matt_alone() { audio_sample_stop_and_free(mus[MATT_ALONE]); return NULL; }
sequence *stop_police_everywhere_p1() { audio_sample_stop_and_free(mus[POLICE_EVERYWHERE_1]); return NULL; }
sequence *stop_mayling_truth() { audio_sample_stop_and_free(mus[MAYLING_TRUTH]); return NULL; }
sequence *start_atmo_train_p1_longer() { mus[ATMO_TRAIN_1_LONGER] = audio_sample_start("EP07 Atmo Ext Train 1 longer", 0, 0.3551822f); return NULL; }
sequence *start_atmo_train_p4_rear() { mus[ATMO_TRAIN_4_REAR] = audio_sample_start("EP07 Atmo Ext Train 4 REAR", 0, 0.3160785f); return NULL; }
sequence *start_atmo_train_p4() { mus[ATMO_TRAIN_4] = audio_sample_start("EP07 Atmo Ext Train 4", 0, 0.2346464f); return NULL; }
sequence *start_atmo_train_p4_2() { mus[ATMO_TRAIN_4] = audio_sample_start("EP07 Atmo Ext Train 4", 0, 0.3478609f); return NULL; }
sequence *start_atmo_train_p4_3() { mus[ATMO_TRAIN_4] = audio_sample_start("EP07 Atmo Ext Train 4", 0, 0.4065775f); return NULL; }
sequence *start_atmo_train_p4_4() { mus[ATMO_TRAIN_4] = audio_sample_start("EP07 Atmo Ext Train 4", 0, 0.427056f); return NULL; }
sequence *start_atmo_train_p4_short() { mus[ATMO_TRAIN_4_SHORT] = audio_sample_start("EP07 Atmo Ext Train 4 short", 0, 0.7106568f); return NULL; }
sequence *start_atmo_train_p5_bass() { mus[ATMO_TRAIN_5_BASS] = audio_sample_start("EP07 Atmo Ext Train 5 bass", 0, 0.3516853f); return NULL; }
sequence *start_forged() { mus[FORGED] = audio_sample_start("EP07 Forged", 0, 0.111812f); return NULL; }
sequence *start_atmo_tunnel() { mus[ATMO_TUNNEL] = audio_sample_start("EP07 Atmo Int Tunnel", 1, 1.0f); return NULL; }
sequence *start_drum_and_bass() { mus[DRUM_AND_BASS] = audio_sample_start("EP07 Drum & Bass", 0, 0.0f); return NULL; }
sequence *start_atmo_police_several_sirens() { mus[ATMO_POLICE_SEVERAL_SIRENS] = audio_sample_start("EP07 Atmo Ext Police Several Sirens 1", 0, 1.0f); return NULL; }
sequence *maybe_start_matt_alone() { if (!game_vars.matt_alone_playing) { mus[MATT_ALONE] = audio_sample_start("EP07 Matt Alone", 0, 0.1114461f); } game_vars.matt_alone_playing = 0; return NULL; }
sequence *change_atmo_train_p5_bass() { audio_sample_set_volume(mus[ATMO_TRAIN_5_BASS], 0.2303271f); return NULL; }
sequence *change_atmo_train_p4() { audio_sample_set_volume(mus[ATMO_TRAIN_4], 0.3040856f); return NULL; }
sequence *change_atmo_train_p4_2() { audio_sample_set_volume(mus[ATMO_TRAIN_4], 0.2822826f); return NULL; }
sequence *change_revellers_p5() { audio_sample_set_volume(mus[ATMO_REVELLERS_5], 1.0f); return NULL; }
sequence *start_mayling_truth() { mus[MAYLING_TRUTH] = audio_sample_start("EP07 MayLing's Truth", 0, 0.1126381f); return NULL; }
sequence *stop_forged() { audio_sample_stop_and_free(mus[FORGED]); return NULL; }
sequence *stop_atmo_train_p1() { audio_sample_stop_and_free(mus[ATMO_TRAIN_1]); return NULL; }
sequence *stop_revellers_p5() { audio_sample_stop_and_free(mus[ATMO_REVELLERS_5]); return NULL; }
sequence *start_atmo_train_p1() { mus[ATMO_TRAIN_1] = audio_sample_start("EP07 Atmo Ext Train 1", 0, 0.3853095f); return NULL; }
sequence *start_atmo_train_p1_2() { mus[ATMO_TRAIN_1] = audio_sample_start("EP07 Atmo Ext Train 1", 0, 0.4462832f); return NULL; }
sequence *start_atmo_train_p1_3() { mus[ATMO_TRAIN_1] = audio_sample_start("EP07 Atmo Ext Train 1", 0, 0.5014004f); return NULL; }
sequence *start_atmo_train_p2() { mus[ATMO_TRAIN_2] = audio_sample_start("EP07 Atmo Ext Train 2", 0, 0.5861539f); return NULL; }
sequence *start_atmo_train_p5() { mus[ATMO_TRAIN_5] = audio_sample_start("EP07 Atmo Ext Train 5", 0, 1.0f); return NULL; }
sequence *start_atmo_train_p5_2() { mus[ATMO_TRAIN_5] = audio_sample_start("EP07 Atmo Ext Train 5", 0, 0.2810671f); return NULL; }
sequence *start_atmo_train_p5_longer() { mus[ATMO_TRAIN_5_LONGER] = audio_sample_start("EP07 Atmo Ext Train 5 longer", 0, 0.3145116f); return NULL; }
sequence *start_atmo_train_p6() { mus[ATMO_TRAIN_6] = audio_sample_start("EP07 Atmo Ext Train 6", 0, 0.3800933f); return NULL; }
sequence *start_atmo_train_p6_2() { mus[ATMO_TRAIN_6] = audio_sample_start("EP07 Atmo Ext Train 6", 0, 0.2803708f); return NULL; }
sequence *start_atmo_train_p4_longer() { mus[ATMO_TRAIN_4_LONGER] = audio_sample_start("EP07 Atmo Ext Train 4 longer", 0, 0.4762116f); return NULL; }
sequence *start_atmo_police_single_siren_2_short() { mus[ATMO_POLICE_SINGLE_SIREN_2] = audio_sample_start("EP07 Atmo Ext Police Single Siren 2 short", 0, 0.2651353f); return NULL; }
sequence *start_atmo_police_single_siren_short() { mus[ATMO_POLICE_SINGLE_SIREN] = audio_sample_start("EP07 Atmo Ext Police Single Siren 1 short", 0, 0.6961312f); return NULL; }
sequence *start_atmo_police_single_siren_short3() { mus[ATMO_POLICE_SINGLE_SIREN] = audio_sample_start("EP07 Atmo Ext Police Single Siren 1 short", 0, 0.7106217f); return NULL; }
sequence *start_atmo_police_single_siren_short2() { mus[ATMO_POLICE_SINGLE_SIREN] = audio_sample_start("EP07 Atmo Ext Police Single Siren 1 short", 0, 0.791577f); return NULL; }
sequence *start_police_everywhere_p1() { mus[POLICE_EVERYWHERE_1] = audio_sample_start("EP07 Police Everywhere I", 0, 0.1112219f); return NULL; }
sequence *start_revellers_p1() { mus[ATMO_REVELLERS_1] = audio_sample_start("EP07 Atmo Ext Revellers 1", 0, 1.0f); return NULL; }
sequence *start_revellers_p2() { mus[ATMO_REVELLERS_2] = audio_sample_start("EP07 Atmo Ext Revellers 2", 0, 1.0f); return NULL; }
sequence *start_revellers_p3() { mus[ATMO_REVELLERS_3] = audio_sample_start("EP07 Atmo Ext Revellers 3", 0, 1.0f); return NULL; }
sequence *start_revellers_p4() { mus[ATMO_REVELLERS_4] = audio_sample_start("EP07 Atmo Ext Revellers 4", 0, 1.0f); return NULL; }
sequence *start_revellers_p5() { mus[ATMO_REVELLERS_5] = audio_sample_start("EP07 Atmo Ext Revellers 5", 0, 0.5608469f); return NULL; }
sequence *start_auction_guy2() { mus[AUCTION_GUY] = audio_sample_start("EP07 Auction Guy", 0, 0.1598199f); return NULL; }
sequence *start_police_everywhere_p2() { mus[POLICE_EVERYWHERE_2] = audio_sample_start("EP07 Police Everywhere II", 0, 0.05980561f); return NULL; }
sequence *start_police_everywhere_p2_2() { mus[POLICE_EVERYWHERE_2] = audio_sample_start("EP07 Police Everywhere II", 0, 0.0706706f); return NULL; }
sequence *start_police_everywhere_p2_3() { mus[POLICE_EVERYWHERE_2] = audio_sample_start("EP07 Police Everywhere II", 0, 0.1583093f); return NULL; }
sequence *start_after_fight() { mus[AFTER_FIGHT] = audio_sample_start("EP07 After Fight", 0, 0.1590764f); return NULL; }
sequence *start_after_fight_trans() { mus[AFTER_FIGHT_TRANS] = audio_sample_start("EP07 After Fight Transition", 0, 0.1593597f); return NULL; }
sequence *maybe_start_intentness_mood() { if (game_vars.passed_by_seg765 || game_vars.passed_by_seg739) { mus[INTENTNESS_MOOD] = audio_sample_start("EP10 Intentness", 0, 0.1121213f); } return NULL; }
sequence *fade_intentness_mood() { audio_sample_fade(mus[INTENTNESS_MOOD], 0.1121213f, 0.2506319f, 3458, 10458); return NULL; }

void fill_events() {
	// OPENING
	// seg101
	install_timed_event(&sequences[0], 0, 0, EVENT_ONESHOT, start_op_bgm);
	install_timed_event(&sequences[0], 21833, 0, EVENT_ONESHOT, fade_op_vol_1);
	install_timed_event(&sequences[0], 22875, 0, EVENT_ONESHOT, fade_op_vol_2);
	install_timed_event(&sequences[0], 24833, 0, EVENT_ONESHOT, fade_op_vol_3);
	install_timed_event(&sequences[0], 26208, 0, EVENT_ONESHOT, fade_op_vol_4);
	install_timed_event(&sequences[0], 27417, 0, EVENT_ONESHOT, fade_op_vol_5);
	install_timed_event(&sequences[0], 30458, 0, EVENT_ONESHOT, fade_op_vol_6);
	// seg102_a (empty)
	// seg102_b (empty)
	// seg106
	install_timed_event(&sequences[3], 8083, 0, EVENT_ONESHOT, start_atmo_station);
	// seg107_a
	install_timed_event(&sequences[4], 0, 0, EVENT_ONESHOT, start_selfish_title);
	install_timed_event(&sequences[4], 10750, 14750, EVENT_DURATION, fade_out_op);
	install_timed_event(&sequences[4], 14750, 0, EVENT_ONESHOT, stop_opening);
	install_timed_event(&sequences[4], 19417, 24500, EVENT_DURATION, fade_out_atmo_station);
	install_timed_event(&sequences[4], 24500, 0, EVENT_ONESHOT, stop_atmo_station);
	// seg107_b
	install_timed_event(&sequences[5], 0, 0, EVENT_ONESHOT, start_selfless_title);
	install_timed_event(&sequences[5], 0, 4000, EVENT_DURATION, fade_out_op2);
	install_timed_event(&sequences[5], 4000, 0, EVENT_ONESHOT, stop_opening);
	install_timed_event(&sequences[5], 17792, 23000, EVENT_DURATION, fade_out_atmo_station2);
	install_timed_event(&sequences[5], 23000, 0, EVENT_ONESHOT, stop_atmo_station);
	// EPISODE 1
	// seg109_110_b_111
	install_timed_event(&sequences[6], 0, 0, EVENT_ONESHOT, stop_opening2);
	install_timed_event(&sequences[6], 108958, 0, EVENT_ONESHOT, start_loneliness_carpark);
	install_timed_event(&sequences[6], 128417, 0, EVENT_ONESHOT, start_garage_atmo);
	install_timed_event(&sequences[6], 128917, 0, EVENT_ONESHOT, stop_atmo_garage);
	install_timed_event(&sequences[6], 185583, 0, EVENT_ONESHOT, start_car_park_melody);
	// seg113_116 (empty)
	// seg114 (empty)
	// seg115 (empty)
	// seg121
	install_timed_event(&sequences[10], 2333, 7750, EVENT_DURATION, fade_car_park_melody);
	install_timed_event(&sequences[10], 7750, 0, EVENT_ONESHOT, start_lee_noise);
	install_timed_event(&sequences[10], 9333, 0, EVENT_ONESHOT, stop_carpark_melody);
	// seg118 (empty)
	// seg119
	install_timed_event(&sequences[12], 10875, 18875, EVENT_DURATION, fade_car_park_melody2);
	install_timed_event(&sequences[12], 18875, 0, EVENT_ONESHOT, stop_carpark_melody);
	// seg117
	install_timed_event(&sequences[13], 4667, 12667, EVENT_DURATION, fade_car_park_melody3);
	install_timed_event(&sequences[13], 12667, 0, EVENT_ONESHOT, stop_carpark_melody);
	// seg128
	install_timed_event(&sequences[14], 5167, 0, EVENT_ONESHOT, start_lee_noise2);
	// seg129
	install_timed_event(&sequences[15], 28292, 0, EVENT_ONESHOT, start_carpark_deal);
	install_timed_event(&sequences[15], 28458, 0, EVENT_ONESHOT, start_scream_close);
	// seg122_a_122_b
	install_timed_event(&sequences[16], 39875, 0, EVENT_ONESHOT, start_lee_noise3);
	// seg136 (empty)
	// seg141
	install_timed_event(&sequences[18], 6917, 0, EVENT_ONESHOT, start_elodie_escape);
	install_timed_event(&sequences[18], 6917, 7917, EVENT_DURATION, fade_car_park_deal);
	install_timed_event(&sequences[18], 7917, 0, EVENT_ONESHOT, stop_carpark_deal);
	// seg139 (empty)
	// seg137
	install_timed_event(&sequences[20], 0, 0, EVENT_ONESHOT, start_lee_stinger);
	install_timed_event(&sequences[20], 500, 0, EVENT_ONESHOT, start_garage_parkfield);
	install_timed_event(&sequences[20], 1500, 0, EVENT_ONESHOT, stop_atmo_garage);
	install_timed_event(&sequences[20], 20542, 0, EVENT_ONESHOT, start_cable_tie);
	// seg138_a_138_b
	install_timed_event(&sequences[21], 11500, 0, EVENT_ONESHOT, start_elodie_escape2);
	install_timed_event(&sequences[21], 11500, 12500, EVENT_DURATION, fade_car_park_deal2);
	install_timed_event(&sequences[21], 12500, 0, EVENT_ONESHOT, stop_carpark_deal);
	// seg133_swipe
	install_timed_event(&sequences[22], 0, 0, EVENT_ONESHOT, start_scream_far);
	// seg134_1 (empty)
	// seg120 (empty)
	// seg140 (empty)
	// seg123 (empty)
	// seg123_tap_130_tap
	install_timed_event(&sequences[27], 0, 0, EVENT_ONESHOT, start_cctv);
	// seg135
	install_timed_event(&sequences[28], 500, 0, EVENT_ONESHOT, start_garage_parkfield);
	install_timed_event(&sequences[28], 1500, 0, EVENT_ONESHOT, stop_atmo_garage);
	install_timed_event(&sequences[28], 12542, 0, EVENT_ONESHOT, start_rope_lee_stinger);
	// seg127
	install_timed_event(&sequences[29], 0, 0, EVENT_ONESHOT, start_carpark_nodeal);
	install_timed_event(&sequences[29], 41, 3625, EVENT_DURATION, fade_car_park_melody4);
	install_timed_event(&sequences[29], 3625, 0, EVENT_ONESHOT, start_weapon_stinger);
	install_timed_event(&sequences[29], 7041, 0, EVENT_ONESHOT, stop_carpark_melody);
	// seg142 (empty)
	// seg143 (empty)
	// seg144
	install_timed_event(&sequences[32], 19958, 22250, EVENT_DURATION, fade_garage_parkfield);
	install_timed_event(&sequences[32], 22250, 0, EVENT_ONESHOT, stop_garage_parkfield);
	// seg145_swipe
	install_timed_event(&sequences[33], 0, 0, EVENT_ONESHOT, start_inside_car);
	install_timed_event(&sequences[33], 2000, 0, EVENT_ONESHOT, stop_carpark_nodeal);
	install_timed_event(&sequences[33], 2000, 0, EVENT_ONESHOT, stop_elodie_escape);
	// seg148_b (empty)
	// seg146_a
	install_timed_event(&sequences[35], 0, 0, EVENT_ONESHOT, start_matt_escape);
	install_timed_event(&sequences[35], 41, 3042, EVENT_DURATION, fade_inside_car);
	install_timed_event(&sequences[35], 3041, 0, EVENT_ONESHOT, stop_inside_car);
	// seg147_a_148_a (empty)
	// seg147_b
	install_timed_event(&sequences[37], 0, 3000, EVENT_DURATION, fade_inside_car2);
	install_timed_event(&sequences[37], 3000, 0, EVENT_ONESHOT, stop_inside_car);
	// seg126
	install_timed_event(&sequences[38], 0, 0, EVENT_ONESHOT, start_carpark_nodeal2);
	// seg134_2 (empty)
	// seg125
	install_timed_event(&sequences[40], 0, 0, EVENT_ONESHOT, start_carpark_nodeal3);
	install_timed_event(&sequences[40], 750, 0, EVENT_ONESHOT, start_weapon_stinger2);
	install_timed_event(&sequences[40], 10792, 0, EVENT_ONESHOT, start_gutted_stinger);
	// seg112_1 (empty)
	// seg112_2_122_b
	install_timed_event(&sequences[213], 42, 7042, EVENT_DURATION, fade_car_park_melody5);
	install_timed_event(&sequences[213], 7042, 0, EVENT_ONESHOT, stop_carpark_melody);
	// EPISODE 2
	// seg201
	install_timed_event(&sequences[41], 0, 0, EVENT_ONESHOT, start_lee_line);
	install_timed_event(&sequences[41], 500, 0, EVENT_ONESHOT, start_atmo_ext_house);
	install_timed_event(&sequences[41], 500, 7000, EVENT_DURATION, fade_matt_escape);
	install_timed_event(&sequences[41], 7000, 0, EVENT_ONESHOT, stop_matt_escape);
	install_timed_event(&sequences[41], 16833, 18875, EVENT_DURATION, fade_lee_line);
	// seg202
	install_timed_event(&sequences[42], 0, 0, EVENT_ONESHOT, maybe_start_matt_escape);
	install_timed_event(&sequences[42], 0, 0, EVENT_ONESHOT, start_atmo_train_station);
	install_timed_event(&sequences[42], 11500, 0, EVENT_ONESHOT, fade_matt_escape2);
	install_timed_event(&sequences[42], 12458, 0, EVENT_ONESHOT, fade_matt_escape3);
	install_timed_event(&sequences[42], 15292, 0, EVENT_ONESHOT, fade_matt_escape2);
	install_timed_event(&sequences[42], 15292, 0, EVENT_ONESHOT, start_atmo_train);
	install_timed_event(&sequences[42], 17417, 0, EVENT_ONESHOT, fade_matt_escape3);
	// seg203 (empty)
	// seg204
	install_timed_event(&sequences[44], 500, 2000, EVENT_DURATION, fade_lee_line2);
	install_timed_event(&sequences[44], 2000, 0, EVENT_ONESHOT, start_showdown_riser);
	install_timed_event(&sequences[44], 24000, 0, EVENT_ONESHOT, stop_atmo_ext_house);
	// seg205
	install_timed_event(&sequences[45], 8400, 0, EVENT_ONESHOT, stop_atmo_ext_house);
	// seg206
	install_timed_event(&sequences[46], 7200, 0, EVENT_ONESHOT, stop_atmo_ext_house);
	// seg207
	install_timed_event(&sequences[47], 7667, 11667, EVENT_DURATION, fade_matt_escape4);
	install_timed_event(&sequences[47], 11667, 0, EVENT_ONESHOT, stop_matt_escape);
	install_timed_event(&sequences[47], 18625, 0, EVENT_ONESHOT, stop_atmo_train_station);
	install_timed_event(&sequences[47], 31417, 0, EVENT_ONESHOT, start_jeff_line);
	install_timed_event(&sequences[47], 36375, 48375, EVENT_DURATION, fade_jeff_line);
	// seg202_1
	install_timed_event(&sequences[48], 208, 0, EVENT_ONESHOT, start_jeff_gun);
	// seg209
	install_timed_event(&sequences[49], 0, 0, EVENT_ONESHOT, start_leg_it);
	install_timed_event(&sequences[49], 1000, 0, EVENT_ONESHOT, stop_matt_escape);
	install_timed_event(&sequences[49], 19958, 0, EVENT_ONESHOT, start_jeff_line);
	install_timed_event(&sequences[49], 26500, 0, EVENT_ONESHOT, stop_atmo_train_station);
	// seg210
	install_timed_event(&sequences[50], 0, 4000, EVENT_DURATION, fade_matt_escape5);
	install_timed_event(&sequences[50], 4000, 0, EVENT_ONESHOT, stop_matt_escape);
	install_timed_event(&sequences[50], 12917, 0, EVENT_ONESHOT, start_jeff_line);
	install_timed_event(&sequences[50], 21500, 0, EVENT_ONESHOT, stop_atmo_train_station);
	// seg208_213_214
	install_timed_event(&sequences[51], 20875, 24375, EVENT_DURATION, fade_jeff_line2);
	install_timed_event(&sequences[51], 60917, 0, EVENT_ONESHOT, start_atmo_house);
	// seg215
	install_timed_event(&sequences[52], 26250, 0, EVENT_ONESHOT, start_any_suggestions);
	// seg216 (empty)
	// seg217
	install_timed_event(&sequences[54], 5375, 0, EVENT_ONESHOT, start_one_less_problem);
	// seg218
	install_timed_event(&sequences[55], 7167, 8167, EVENT_DURATION, fade_any_suggestions);
	install_timed_event(&sequences[55], 8167, 0, EVENT_ONESHOT, stop_any_suggestions);
	// seg219
	install_timed_event(&sequences[56], 3417, 12400, EVENT_DURATION, fade_any_suggestions2);
	install_timed_event(&sequences[56], 12400, 0, EVENT_ONESHOT, stop_any_suggestions);
	// seg220_1 (empty)
	// seg220_2
	install_timed_event(&sequences[58], 14667, 0, EVENT_ONESHOT, start_pushing);
	install_timed_event(&sequences[58], 16000, 20000, EVENT_DURATION, fade_one_less_problem);
	install_timed_event(&sequences[58], 20000, 0, EVENT_ONESHOT, stop_one_less_problem);
	// seg223 (empty)
	// seg224 (empty)
	// seg225
	install_timed_event(&sequences[61], 14792, 0, EVENT_ONESHOT, start_pushing);
	install_timed_event(&sequences[61], 16292, 20292, EVENT_DURATION, fade_one_less_problem2);
	install_timed_event(&sequences[61], 20292, 0, EVENT_ONESHOT, stop_one_less_problem);
	// seg226_1 (empty)
	// seg226
	install_timed_event(&sequences[63], 18333, 0, EVENT_ONESHOT, start_lets_go);
	install_timed_event(&sequences[63], 20000, 0, EVENT_ONESHOT, stop_pushing);
	install_timed_event(&sequences[63], 20150, 0, EVENT_ONESHOT, fade_lets_go);
	install_timed_event(&sequences[63], 20300, 0, EVENT_ONESHOT, stop_atmo_house);
	// seg212
	install_timed_event(&sequences[64], 0, 0, EVENT_ONESHOT, start_atmo_house);
	install_timed_event(&sequences[64], 0, 20000, EVENT_DURATION, fade_lee_line3);
	install_timed_event(&sequences[64], 20000, 0, EVENT_ONESHOT, stop_lee_line);
	// seg230 (empty)
	// seg228 (empty)
	// seg229 (empty)
	// seg227 (empty)
	// seg231
	install_timed_event(&sequences[69], 10292, 19292, EVENT_DURATION, fade_pushing);
	install_timed_event(&sequences[63], 19292, 0, EVENT_ONESHOT, start_lets_go2);
	install_timed_event(&sequences[69], 20292, 0, EVENT_ONESHOT, stop_pushing);
	install_timed_event(&sequences[69], 20292, 21625, EVENT_DURATION, fade_lets_go2);
	install_timed_event(&sequences[69], 21625, 0, EVENT_ONESHOT, stop_atmo_house);
	// EPISODE 3
	// seg301_1_301_2
	install_timed_event(&sequences[70], 10625, 0, EVENT_ONESHOT, start_matt_vo);
	install_timed_event(&sequences[70], 11000, 0, EVENT_ONESHOT, fade_lets_go3);
	install_timed_event(&sequences[70], 17000, 18000, EVENT_DURATION, fade_lets_go4);
	install_timed_event(&sequences[70], 25750, 0, EVENT_ONESHOT, start_atmo_entrance);
	install_timed_event(&sequences[70], 26875, 0, EVENT_ONESHOT, start_auction_guy);
	install_timed_event(&sequences[70], 73958, 0, EVENT_ONESHOT, start_dance);
	install_timed_event(&sequences[70], 73958, 79958, EVENT_DURATION, fade_dance);
	install_timed_event(&sequences[70], 80583, 0, EVENT_ONESHOT, stop_auction_guy);
	// seg302_a
	install_timed_event(&sequences[71], 9500, 0, EVENT_ONESHOT, stop_atmo_entrance);
	// seg302_b
	install_timed_event(&sequences[72], 7500, 0, EVENT_ONESHOT, stop_atmo_entrance);
	// seg303_310
	install_timed_event(&sequences[73], 0, 0, EVENT_ONESHOT, change_dance);
	install_timed_event(&sequences[73], 17958, 0, EVENT_ONESHOT, change_dance2);
	install_timed_event(&sequences[73], 18458, 0, EVENT_ONESHOT, start_atmo_auction);
	install_timed_event(&sequences[73], 25542, 0, EVENT_ONESHOT, start_taking_seats);
	install_timed_event(&sequences[73], 69083, 79083, EVENT_DURATION, fade_taking_seats);
	install_timed_event(&sequences[73], 79083, 0, EVENT_ONESHOT, stop_taking_seats);
	install_timed_event(&sequences[73], 80542, 0, EVENT_ONESHOT, stop_dance);
	install_timed_event(&sequences[73], 82333, 0, EVENT_ONESHOT, start_bowl_auction);
	install_timed_event(&sequences[73], 90917, 92917, EVENT_DURATION, fade_bowl_auction);
	install_timed_event(&sequences[73], 148625, 0, EVENT_ONESHOT, start_bidding_flache);
	install_timed_event(&sequences[73], 158625, 160625, EVENT_DURATION, fade_bidding_flache);
	// seg311
	install_timed_event(&sequences[74], 70667, 73417, EVENT_DURATION, seg314_1);
	// seg312
	install_timed_event(&sequences[75], 0, 0, EVENT_ONESHOT, start_bidding_riser_1);
	install_timed_event(&sequences[75], 39417, 0, EVENT_ONESHOT, start_dance2);
	install_timed_event(&sequences[75], 39458, 0, EVENT_ONESHOT, stop_atmo_auction);
	install_timed_event(&sequences[75], 39750, 0, EVENT_ONESHOT, start_atmo_hall);
	install_timed_event(&sequences[75], 39750, 45250, EVENT_DURATION, fade_bidding_riser_1);
	install_timed_event(&sequences[75], 45250, 0, EVENT_ONESHOT, stop_bidding_flache);
	install_timed_event(&sequences[75], 45250, 0, EVENT_ONESHOT, stop_bidding_riser_1);
	// seg314_1
	install_timed_event(&sequences[76], 0, 0, EVENT_ONESHOT, start_bidding_riser_2);
	install_timed_event(&sequences[76], 2000, 0, EVENT_ONESHOT, stop_bidding_flache);
	// seg314_2
	install_timed_event(&sequences[77], 0, 0, EVENT_ONESHOT, start_bidding_riser_2);
	install_timed_event(&sequences[77], 2000, 0, EVENT_ONESHOT, stop_bidding_flache);
	// seg313
	install_timed_event(&sequences[78], 0, 0, EVENT_ONESHOT, start_bidding_riser_let_her);
	install_timed_event(&sequences[78], 57500, 0, EVENT_ONESHOT, start_dance3);
	install_timed_event(&sequences[78], 57583, 0, EVENT_ONESHOT, stop_atmo_auction);
	install_timed_event(&sequences[78], 57912, 0, EVENT_ONESHOT, start_atmo_hall);
	install_timed_event(&sequences[78], 57912, 62250, EVENT_DURATION, fade_bidding_riser_let_her);
	install_timed_event(&sequences[78], 62250, 0, EVENT_ONESHOT, stop_bidding_riser_let_her);
	// seg315
	install_timed_event(&sequences[79], 0, 5250, EVENT_DURATION, fade_bidding_flache2);
	install_timed_event(&sequences[79], 5250, 0, EVENT_ONESHOT, stop_bidding_flache);
	install_timed_event(&sequences[79], 6750, 0, EVENT_ONESHOT, start_car_park_elevator);
	install_timed_event(&sequences[79], 6750, 10250, EVENT_DURATION, fade_dance2);
	install_timed_event(&sequences[79], 10250, 0, EVENT_ONESHOT, stop_dance);
	// seg316_b
	install_timed_event(&sequences[80], 14200, 0, EVENT_ONESHOT, stop_atmo_hall);
	// seg316_c
	install_timed_event(&sequences[81], 14200, 0, EVENT_ONESHOT, stop_atmo_hall);
	// seg317 (empty)
	// seg318 (empty)
	// seg343_344_a
	install_timed_event(&sequences[84], 42, 0, EVENT_ONESHOT, start_atmo_basement);
	install_timed_event(&sequences[84], 7500, 10500, EVENT_DURATION, fade_car_park_elevator);
	install_timed_event(&sequences[84], 10500, 0, EVENT_ONESHOT, stop_car_park_elevator);
	install_timed_event(&sequences[84], 12917, 0, EVENT_ONESHOT, start_brutal_p1);
	// seg343_344_b
	install_timed_event(&sequences[85], 0, 0, EVENT_ONESHOT, start_atmo_basement);
	install_timed_event(&sequences[85], 6333, 9333, EVENT_DURATION, fade_car_park_elevator2);
	install_timed_event(&sequences[85], 9333, 0, EVENT_ONESHOT, stop_car_park_elevator);
	install_timed_event(&sequences[85], 10167, 0, EVENT_ONESHOT, start_brutal_p1_2);
	// seg314
	install_timed_event(&sequences[86], 18667, 0, EVENT_ONESHOT, stop_atmo_auction);
	install_timed_event(&sequences[86], 18750, 0, EVENT_ONESHOT, start_atmo_hall);
	install_timed_event(&sequences[86], 18792, 0, EVENT_ONESHOT, start_dance4);
	install_timed_event(&sequences[86], 18833, 24833, EVENT_DURATION, fade_bidding_riser_2);
	install_timed_event(&sequences[86], 24883, 0, EVENT_ONESHOT, stop_bidding_riser_2);
	// seg345 (empty)
	// seg319
	install_timed_event(&sequences[88], 16000, 0, EVENT_ONESHOT, start_awareness);
	install_timed_event(&sequences[88], 16000, 19000, EVENT_DURATION, fade_car_park_elevator3);
	install_timed_event(&sequences[88], 19000, 0, EVENT_ONESHOT, stop_car_park_elevator);
	// seg320_k (empty)
	// seg322
	install_timed_event(&sequences[90], 7625, 0, EVENT_ONESHOT, start_atmo_inside_office);
	// seg322_tap (empty)
	// seg326_324
	install_timed_event(&sequences[92], 22375, 0, EVENT_ONESHOT, stop_atmo_inside_office);
	install_timed_event(&sequences[92], 22417, 0, EVENT_ONESHOT, start_atmo_outside_office);
	// seg327
	install_timed_event(&sequences[93], 5083, 0, EVENT_ONESHOT, start_awareness_downlifter);
	install_timed_event(&sequences[93], 5083, 6792, EVENT_DURATION, fade_awareness);
	install_timed_event(&sequences[93], 6792, 0, EVENT_ONESHOT, stop_awareness);
	install_timed_event(&sequences[93], 12000, 0, EVENT_ONESHOT, start_hainsworth_office);
	// seg328
	install_timed_event(&sequences[94], 10333, 20333, EVENT_DURATION, fade_hainsworth_office);
	// seg329
	install_timed_event(&sequences[95], 13125, 21000, EVENT_DURATION, fade_hainsworth_office2);
	// seg329_1 (empty)
	// seg331
	install_timed_event(&sequences[97], 167, 0, EVENT_ONESHOT, stop_atmo_inside_office);
	install_timed_event(&sequences[97], 12583, 0, EVENT_ONESHOT, start_hainsworth_elevator);
	install_timed_event(&sequences[97], 12583, 14500, EVENT_DURATION, fade_hainsworth_office3);
	install_timed_event(&sequences[97], 14500, 0, EVENT_ONESHOT, stop_hainsworth_office);
	// seg333 (empty)
	// seg346_350_352
	install_timed_event(&sequences[99], 21125, 0, EVENT_ONESHOT, start_brutal_p1_3);
	install_timed_event(&sequences[99], 22083, 0, EVENT_ONESHOT, start_awareness_downlifter2);
	install_timed_event(&sequences[99], 33875, 0, EVENT_ONESHOT, start_freight);
	install_timed_event(&sequences[99], 33875, 37000, EVENT_DURATION, fade_brutal_p1);
	install_timed_event(&sequences[99], 37000, 0, EVENT_ONESHOT, start_brutal_p2);
	install_timed_event(&sequences[99], 39000, 0, EVENT_ONESHOT, stop_brutal_p1);
	install_timed_event(&sequences[99], 52792, 60792, EVENT_DURATION, fade_brutal_p2);
	// seg354 (empty)
	// seg365_366
	install_timed_event(&sequences[101], 542, 2542, EVENT_DURATION, fade_brutal_p2_2);
	install_timed_event(&sequences[101], 4750, 6750, EVENT_DURATION, fade_brutal_p2_3);
	install_timed_event(&sequences[101], 11583, 0, EVENT_ONESHOT, start_alarm);
	install_timed_event(&sequences[101], 30250, 35250, EVENT_DURATION, fade_brutal_p2_4);
	install_timed_event(&sequences[101], 41750, 0, EVENT_ONESHOT, start_hainsworth_lobby);
	install_timed_event(&sequences[101], 43750, 0, EVENT_ONESHOT, stop_atmo_basement_guard);
	// seg342
	install_timed_event(&sequences[102], 31917, 0, EVENT_ONESHOT, maybe_start_get_away_riser);
	install_timed_event(&sequences[102], 38167, 42792, EVENT_DURATION, fade_alarm);
	install_timed_event(&sequences[102], 42792, 0, EVENT_ONESHOT, stop_alarm);
	install_timed_event(&sequences[102], 42792, 0, EVENT_ONESHOT, maybe_start_get_away_long);
	// seg335
	install_timed_event(&sequences[103], 3500, 0, EVENT_ONESHOT, start_atmo_basement_sebastien);
	install_timed_event(&sequences[103], 9625, 0, EVENT_ONESHOT, start_brutal_p3);
	install_timed_event(&sequences[103], 9625, 13167, EVENT_ONESHOT, fade_multiple);
	install_timed_event(&sequences[103], 13167, 0, EVENT_ONESHOT, stop_awareness);
	install_timed_event(&sequences[103], 13167, 0, EVENT_ONESHOT, stop_hainsworth_elevator);
	// seg341
	install_timed_event(&sequences[104], 292, 0, EVENT_ONESHOT, start_alarm2);
	install_timed_event(&sequences[104], 292, 7250, EVENT_DURATION, fade_brutal_p3);
	install_timed_event(&sequences[104], 7250, 0, EVENT_ONESHOT, start_hainsworth_lobby2);
	install_timed_event(&sequences[104], 9000, 0, EVENT_ONESHOT, stop_brutal_p3);
	install_timed_event(&sequences[104], 10042, 0, EVENT_ONESHOT, stop_atmo_basement_sebastien);
	// seg338 (empty)
	// seg339
	install_timed_event(&sequences[106], 0, 0, EVENT_ONESHOT, start_brutal_riser);
	// seg340
	install_timed_event(&sequences[107], 26458, 0, EVENT_ONESHOT, start_get_away_long);
	install_timed_event(&sequences[107], 27667, 0, EVENT_ONESHOT, stop_atmo_basement_sebastien);
	install_timed_event(&sequences[107], 27833, 0, EVENT_ONESHOT, stop_brutal_p3);
	// seg330
	install_timed_event(&sequences[108], 11708, 0, EVENT_ONESHOT, stop_atmo_inside_office);
	install_timed_event(&sequences[108], 17625, 0, EVENT_ONESHOT, start_hainsworth_elevator2);
	install_timed_event(&sequences[108], 17625, 20000, EVENT_DURATION, fade_hainsworth_office4);
	install_timed_event(&sequences[108], 20000, 0, EVENT_ONESHOT, stop_hainsworth_office);
	// seg349_355_356
	install_timed_event(&sequences[109], 21208, 0, EVENT_ONESHOT, start_awareness_downlifter3);
	install_timed_event(&sequences[109], 21208, 25458, EVENT_DURATION, fade_brutal_p1_2);
	install_timed_event(&sequences[109], 25458, 0, EVENT_ONESHOT, start_freight2);
	install_timed_event(&sequences[109], 34875, 0, EVENT_ONESHOT, start_brutal_p2_2);
	install_timed_event(&sequences[109], 34875, 42583, EVENT_DURATION, fade_brutal_p1_3);
	install_timed_event(&sequences[109], 42583, 0, EVENT_ONESHOT, stop_brutal_p1);
	// seg357 (empty)
	// seg358_359
	install_timed_event(&sequences[111], 13458, 0, EVENT_ONESHOT, start_brutal_keypad);
	install_timed_event(&sequences[111], 13500, 22500, EVENT_DURATION, fade_brutal_p2_5);
	install_timed_event(&sequences[111], 22500, 0, EVENT_ONESHOT, stop_brutal_p2);
	// seg364_367_a_368 (empty)
	// seg364_367_b_368 (empty)
	// seg321_324
	install_timed_event(&sequences[114], 0, 0, EVENT_ONESHOT, start_atmo_inside_office);
	install_timed_event(&sequences[114], 3000, 0, EVENT_ONESHOT, start_hainsworth_stairs);
	install_timed_event(&sequences[114], 3000, 6000, EVENT_DURATION, fade_awareness2);
	install_timed_event(&sequences[114], 6000, 0, EVENT_ONESHOT, stop_awareness);
	// seg325_a
	install_timed_event(&sequences[115], 7833, 0, EVENT_ONESHOT, stop_atmo_outside_office);
	install_timed_event(&sequences[115], 10292, 0, EVENT_ONESHOT, maybe_start_hainsworth_elevator);
	install_timed_event(&sequences[115], 11000, 0, EVENT_ONESHOT, stop_hainsworth_stairs);
	// seg325_b
	install_timed_event(&sequences[116], 7042, 0, EVENT_ONESHOT, stop_atmo_outside_office);
	install_timed_event(&sequences[116], 8958, 0, EVENT_ONESHOT, maybe_start_hainsworth_elevator);
	install_timed_event(&sequences[116], 11000, 0, EVENT_ONESHOT, stop_hainsworth_stairs);
	// seg334
	install_timed_event(&sequences[117], 8625, 18625, EVENT_DURATION, fade_hainsworth_office5);
	// seg336 (empty)
	// seg337 (empty)
	// seg360 (empty)
	// seg361 (empty)
	// seg362
	install_timed_event(&sequences[122], 7000, 8000, EVENT_DURATION, fade_brutal_p2_6);
	install_timed_event(&sequences[122], 15667, 0, EVENT_ONESHOT, start_brutal_keypad2);
	install_timed_event(&sequences[122], 16667, 25667, EVENT_DURATION, fade_brutal_p2_7);
	install_timed_event(&sequences[122], 25667, 0, EVENT_ONESHOT, stop_brutal_p2);
	// seg363
	install_timed_event(&sequences[123], 83, 3083, EVENT_DURATION, fade_brutal_p2_8);
	install_timed_event(&sequences[123], 9375, 0, EVENT_ONESHOT, start_brutal_keypad);
	install_timed_event(&sequences[123], 9375, 17833, EVENT_DURATION, fade_brutal_p2_9);
	install_timed_event(&sequences[123], 17833, 0, EVENT_ONESHOT, stop_brutal_p2);
	// seg369_1k (empty)
	// seg369_2k (empty)
	// seg370_375
	install_timed_event(&sequences[126], 8250, 0, EVENT_ONESHOT, start_get_away_long2);
	install_timed_event(&sequences[126], 9000, 0, EVENT_ONESHOT, stop_brutal_keypad);
	install_timed_event(&sequences[126], 10125, 0, EVENT_ONESHOT, stop_atmo_basement_guard);
	// seg373_374_366
	install_timed_event(&sequences[127], 5667, 0, EVENT_ONESHOT, start_alarm);
	install_timed_event(&sequences[127], 6000, 0, EVENT_ONESHOT, stop_brutal_keypad);
	install_timed_event(&sequences[127], 28375, 0, EVENT_ONESHOT, start_hainsworth_lobby3);
	install_timed_event(&sequences[127], 30500, 0, EVENT_ONESHOT, stop_atmo_basement_guard);
	// EPISODE 4
	// seg415_418
	install_timed_event(&sequences[128], 0, 0, EVENT_ONESHOT, start_get_away_short);
	install_timed_event(&sequences[128], 42, 0, EVENT_ONESHOT, start_siren);
	install_timed_event(&sequences[128], 12167, 0, EVENT_ONESHOT, change_get_away_short);
	install_timed_event(&sequences[128], 13000, 0, EVENT_ONESHOT, change_get_away_short2);
	install_timed_event(&sequences[128], 13667, 0, EVENT_ONESHOT, start_bmw_i8);
	install_timed_event(&sequences[128], 14083, 0, EVENT_ONESHOT, change_get_away_short3);
	install_timed_event(&sequences[128], 16333, 0, EVENT_ONESHOT, change_get_away_short4);
	install_timed_event(&sequences[128], 18708, 0, EVENT_ONESHOT, change_get_away_short5);
	install_timed_event(&sequences[128], 19875, 0, EVENT_ONESHOT, change_get_away_short6);
	// seg415_416
	install_timed_event(&sequences[129], 0, 0, EVENT_ONESHOT, start_get_away_short);
	install_timed_event(&sequences[129], 42, 0, EVENT_ONESHOT, start_siren);
	install_timed_event(&sequences[129], 12542, 0, EVENT_ONESHOT, change_get_away_short);
	install_timed_event(&sequences[129], 13208, 0, EVENT_ONESHOT, change_get_away_short2);
	install_timed_event(&sequences[129], 13667, 0, EVENT_ONESHOT, start_bmw_i8);
	install_timed_event(&sequences[129], 15458, 0, EVENT_ONESHOT, change_get_away_short3);
	install_timed_event(&sequences[129], 18542, 0, EVENT_ONESHOT, change_get_away_short4);
	// seg402
	install_timed_event(&sequences[130], 0, 0, EVENT_ONESHOT, maybe_start_get_away_long2);
	install_timed_event(&sequences[130], 42, 0, EVENT_ONESHOT, start_siren);
	install_timed_event(&sequences[130], 9833, 0, EVENT_ONESHOT, change_get_away_long);
	install_timed_event(&sequences[130], 10542, 0, EVENT_ONESHOT, change_get_away_long2);
	install_timed_event(&sequences[130], 22667, 0, EVENT_ONESHOT, change_get_away_long3);
	install_timed_event(&sequences[130], 24208, 0, EVENT_ONESHOT, change_get_away_long4);
	// seg406
	install_timed_event(&sequences[131], 0, 0, EVENT_ONESHOT, maybe_start_get_away_long2);
	install_timed_event(&sequences[131], 42, 0, EVENT_ONESHOT, start_siren);
	// seg407_a
	install_timed_event(&sequences[132], 0, 0, EVENT_ONESHOT, start_bmw_m5);
	install_timed_event(&sequences[132], 2250, 0, EVENT_ONESHOT, change_get_away_long3);
	install_timed_event(&sequences[132], 4667, 0, EVENT_ONESHOT, change_get_away_long4);
	// seg407_b
	install_timed_event(&sequences[133], 42, 0, EVENT_ONESHOT, start_bmw_m5);
	install_timed_event(&sequences[133], 2542, 0, EVENT_ONESHOT, change_get_away_long3);
	install_timed_event(&sequences[133], 5333, 0, EVENT_ONESHOT, change_get_away_long4);
	install_timed_event(&sequences[133], 8375, 0, EVENT_ONESHOT, change_get_away_long3);
	install_timed_event(&sequences[133], 9708, 0, EVENT_ONESHOT, change_get_away_long4);
	// seg408
	install_timed_event(&sequences[134], 3708, 0, EVENT_ONESHOT, change_get_away_long3);
	install_timed_event(&sequences[134], 5208, 0, EVENT_ONESHOT, change_get_away_long4);
	install_timed_event(&sequences[134], 7417, 0, EVENT_ONESHOT, change_get_away_long3);
	install_timed_event(&sequences[134], 7375, 0, EVENT_ONESHOT, change_get_away_long4);
	install_timed_event(&sequences[134], 8333, 0, EVENT_ONESHOT, change_get_away_long3);
	install_timed_event(&sequences[134], 10583, 0, EVENT_ONESHOT, change_get_away_long4);
	// seg403_a
	install_timed_event(&sequences[135], 0, 0, EVENT_ONESHOT, start_bmw_m5);
	install_timed_event(&sequences[135], 208, 0, EVENT_ONESHOT, change_get_away_long3);
	install_timed_event(&sequences[135], 1542, 0, EVENT_ONESHOT, change_get_away_long4);
	install_timed_event(&sequences[135], 2375, 0, EVENT_ONESHOT, change_get_away_long3);
	install_timed_event(&sequences[135], 3292, 0, EVENT_ONESHOT, change_get_away_long4);
	install_timed_event(&sequences[135], 8208, 0, EVENT_ONESHOT, change_get_away_long3);
	install_timed_event(&sequences[135], 10708, 0, EVENT_ONESHOT, change_get_away_long4);
	install_timed_event(&sequences[135], 11667, 0, EVENT_ONESHOT, change_get_away_long3);
	install_timed_event(&sequences[135], 13542, 0, EVENT_ONESHOT, change_get_away_long4);
	// seg403_b
	install_timed_event(&sequences[136], 0, 0, EVENT_ONESHOT, start_bmw_m5);
	install_timed_event(&sequences[136], 5625, 0, EVENT_ONESHOT, change_get_away_long3);
	install_timed_event(&sequences[136], 6542, 0, EVENT_ONESHOT, change_get_away_long4);
	install_timed_event(&sequences[136], 8708, 0, EVENT_ONESHOT, change_get_away_long3);
	install_timed_event(&sequences[136], 11208, 0, EVENT_ONESHOT, change_get_away_long4);
	install_timed_event(&sequences[136], 13125, 0, EVENT_ONESHOT, change_get_away_long3);
	install_timed_event(&sequences[136], 17250, 0, EVENT_ONESHOT, change_get_away_long4);
	// seg404_a
	install_timed_event(&sequences[137], 58, 0, EVENT_ONESHOT, change_get_away_long3);
	install_timed_event(&sequences[137], 875, 0, EVENT_ONESHOT, change_get_away_long4);
	install_timed_event(&sequences[137], 1708, 0, EVENT_ONESHOT, change_get_away_long3);
	install_timed_event(&sequences[137], 2125, 0, EVENT_ONESHOT, change_get_away_long4);
	install_timed_event(&sequences[137], 8583, 0, EVENT_ONESHOT, stop_bmw_m5);
	// seg404_b
	install_timed_event(&sequences[138], 9833, 0, EVENT_ONESHOT, stop_bmw_m5);
	// seg407_c (empty)
	// seg409
	install_timed_event(&sequences[140], 1625, 0, EVENT_ONESHOT, change_get_away_long3);
	install_timed_event(&sequences[140], 2458, 0, EVENT_ONESHOT, change_get_away_long4);
	install_timed_event(&sequences[140], 12250, 0, EVENT_ONESHOT, stop_bmw_m5);
	// seg410
	install_timed_event(&sequences[141], 9042, 0, EVENT_ONESHOT, change_get_away_long3);
	install_timed_event(&sequences[141], 9958, 0, EVENT_ONESHOT, change_get_away_long4);
	install_timed_event(&sequences[141], 12417, 0, EVENT_ONESHOT, change_get_away_long3);
	install_timed_event(&sequences[141], 14958, 0, EVENT_ONESHOT, change_get_away_long4);
	install_timed_event(&sequences[141], 16750, 0, EVENT_ONESHOT, change_get_away_long3);
	install_timed_event(&sequences[141], 18458, 0, EVENT_ONESHOT, change_get_away_long4);
	install_timed_event(&sequences[141], 20667, 0, EVENT_ONESHOT, change_get_away_long3);
	install_timed_event(&sequences[141], 20875, 0, EVENT_ONESHOT, change_get_away_long4);
	// seg411_a
	install_timed_event(&sequences[142], 5625, 0, EVENT_ONESHOT, change_get_away_long3);
	install_timed_event(&sequences[142], 6167, 0, EVENT_ONESHOT, change_get_away_long4);
	// seg411_b
	install_timed_event(&sequences[143], 58, 0, EVENT_ONESHOT, change_get_away_long3);
	install_timed_event(&sequences[143], 3417, 0, EVENT_ONESHOT, change_get_away_long4);
	install_timed_event(&sequences[143], 5958, 0, EVENT_ONESHOT, change_get_away_long3);
	install_timed_event(&sequences[143], 7042, 0, EVENT_ONESHOT, change_get_away_long4);
	install_timed_event(&sequences[143], 8625, 0, EVENT_ONESHOT, change_get_away_long3);
	install_timed_event(&sequences[143], 12000, 0, EVENT_ONESHOT, change_get_away_long4);
	install_timed_event(&sequences[143], 13250, 0, EVENT_ONESHOT, change_get_away_long3);
	install_timed_event(&sequences[143], 13958, 0, EVENT_ONESHOT, change_get_away_long4);
	install_timed_event(&sequences[143], 14917, 0, EVENT_ONESHOT, change_get_away_long3);
	install_timed_event(&sequences[143], 17708, 0, EVENT_ONESHOT, change_get_away_long4);
	install_timed_event(&sequences[143], 25208, 0, EVENT_ONESHOT, stop_bmw_m5);
	// seg412
	install_timed_event(&sequences[144], 17, 0, EVENT_ONESHOT, change_get_away_long3);
	install_timed_event(&sequences[144], 2667, 0, EVENT_ONESHOT, change_get_away_long4);
	install_timed_event(&sequences[144], 3708, 0, EVENT_ONESHOT, change_get_away_long3);
	install_timed_event(&sequences[144], 4542, 0, EVENT_ONESHOT, change_get_away_long4);
	// seg413
	install_timed_event(&sequences[145], 42, 0, EVENT_ONESHOT, change_get_away_long3);
	install_timed_event(&sequences[145], 3375, 0, EVENT_ONESHOT, change_get_away_long4);
	install_timed_event(&sequences[145], 4833, 0, EVENT_ONESHOT, change_get_away_long3);
	install_timed_event(&sequences[145], 6333, 0, EVENT_ONESHOT, change_get_away_long4);
	install_timed_event(&sequences[145], 7458, 0, EVENT_ONESHOT, change_get_away_long3);
	install_timed_event(&sequences[145], 13042, 0, EVENT_ONESHOT, change_get_away_long4);
	install_timed_event(&sequences[145], 18167, 0, EVENT_ONESHOT, stop_bmw_m5);
	// seg417_a
	install_timed_event(&sequences[146], 375, 0, EVENT_ONESHOT, change_get_away_short3);
	install_timed_event(&sequences[146], 2375, 0, EVENT_ONESHOT, change_get_away_short4);
	install_timed_event(&sequences[146], 3125, 0, EVENT_ONESHOT, change_get_away_short3);
	install_timed_event(&sequences[146], 12542, 0, EVENT_ONESHOT, change_get_away_short4);
	install_timed_event(&sequences[146], 14167, 0, EVENT_ONESHOT, change_get_away_short3);
	install_timed_event(&sequences[146], 16708, 0, EVENT_ONESHOT, change_get_away_short4);
	// seg417_b (empty)
	// seg405
	install_timed_event(&sequences[148], 42, 0, EVENT_ONESHOT, change_get_away_long3);
	install_timed_event(&sequences[148], 92, 0, EVENT_ONESHOT, change_get_away_long4);
	install_timed_event(&sequences[148], 1792, 0, EVENT_ONESHOT, change_get_away_long3);
	install_timed_event(&sequences[148], 3833, 0, EVENT_ONESHOT, change_get_away_long4);
	install_timed_event(&sequences[148], 4833, 0, EVENT_ONESHOT, change_get_away_long3);
	install_timed_event(&sequences[148], 8083, 0, EVENT_ONESHOT, change_get_away_long4);
	install_timed_event(&sequences[148], 8958, 0, EVENT_ONESHOT, change_get_away_long3);
	install_timed_event(&sequences[148], 9667, 0, EVENT_ONESHOT, change_get_away_long4);
	install_timed_event(&sequences[148], 10917, 0, EVENT_ONESHOT, change_get_away_long3);
	install_timed_event(&sequences[148], 11792, 0, EVENT_ONESHOT, change_get_away_long4);
	// seg419
	install_timed_event(&sequences[149], 333, 0, EVENT_ONESHOT, change_get_away_short3);
	install_timed_event(&sequences[149], 792, 0, EVENT_ONESHOT, change_get_away_short4);
	install_timed_event(&sequences[149], 1208, 0, EVENT_ONESHOT, change_get_away_short3);
	install_timed_event(&sequences[149], 1625, 0, EVENT_ONESHOT, change_get_away_short4);
	install_timed_event(&sequences[149], 2917, 0, EVENT_ONESHOT, change_get_away_short3);
	install_timed_event(&sequences[149], 3417, 0, EVENT_ONESHOT, change_get_away_short4);
	install_timed_event(&sequences[149], 6708, 0, EVENT_ONESHOT, change_get_away_short3);
	install_timed_event(&sequences[149], 8583, 0, EVENT_ONESHOT, change_get_away_short4);
	install_timed_event(&sequences[149], 9250, 0, EVENT_ONESHOT, change_get_away_short3);
	install_timed_event(&sequences[149], 10333, 0, EVENT_ONESHOT, change_get_away_short4);
	install_timed_event(&sequences[149], 12833, 0, EVENT_ONESHOT, change_get_away_short3);
	install_timed_event(&sequences[149], 14042, 0, EVENT_ONESHOT, change_get_away_short4);
	// seg414
	install_timed_event(&sequences[150], 0, 2000, EVENT_DURATION, fade_bmw_m5);
	install_timed_event(&sequences[150], 2000, 0, EVENT_ONESHOT, stop_bmw_m5);
	install_timed_event(&sequences[150], 25000, 0, EVENT_ONESHOT, change_get_away_long3);
	install_timed_event(&sequences[150], 25250, 0, EVENT_ONESHOT, change_get_away_long4);
	install_timed_event(&sequences[150], 25958, 0, EVENT_ONESHOT, change_get_away_long3);
	install_timed_event(&sequences[150], 28250, 0, EVENT_ONESHOT, change_get_away_long4);
	// seg420
	install_timed_event(&sequences[151], 0, 0, EVENT_ONESHOT, stop_bmw_i8);
	// seg421_a
	install_timed_event(&sequences[152], 3625, 0, EVENT_ONESHOT, change_get_away_short3);
	install_timed_event(&sequences[152], 3833, 0, EVENT_ONESHOT, change_get_away_short4);
	install_timed_event(&sequences[152], 4625, 0, EVENT_ONESHOT, change_get_away_short3);
	install_timed_event(&sequences[152], 5125, 0, EVENT_ONESHOT, change_get_away_short4);
	install_timed_event(&sequences[152], 6083, 0, EVENT_ONESHOT, change_get_away_short3);
	install_timed_event(&sequences[152], 7208, 0, EVENT_ONESHOT, change_get_away_short4);
	install_timed_event(&sequences[152], 7917, 0, EVENT_ONESHOT, change_get_away_short3);
	install_timed_event(&sequences[152], 8167, 0, EVENT_ONESHOT, change_get_away_short4);
	install_timed_event(&sequences[152], 8875, 0, EVENT_ONESHOT, change_get_away_short3);
	install_timed_event(&sequences[152], 10583, 0, EVENT_ONESHOT, change_get_away_short4);
	// seg434
	install_timed_event(&sequences[153], 2250, 0, EVENT_ONESHOT, change_get_away_short7);
	install_timed_event(&sequences[153], 2250, 0, EVENT_ONESHOT, change_get_away_long5);
	install_timed_event(&sequences[153], 31083, 32042, EVENT_DURATION, seg435_a_event);
	// seg435_a
	install_timed_event(&sequences[154], 0, 0, EVENT_ONESHOT, start_ford_transit);
	// seg435_b
	install_timed_event(&sequences[155], 0, 0, EVENT_ONESHOT, start_fire);
	// seg435_c
	install_timed_event(&sequences[156], 0, 0, EVENT_ONESHOT, start_ford_transit);
	// seg436_437
	install_timed_event(&sequences[157], 2375, 0, EVENT_ONESHOT, start_get_away_riser_new);
	install_timed_event(&sequences[157], 2375, 4375, EVENT_DURATION, fade_get_away_long);
	install_timed_event(&sequences[157], 4375, 0, EVENT_ONESHOT, stop_get_away_short);
	install_timed_event(&sequences[157], 4375, 0, EVENT_ONESHOT, stop_get_away_long);
	install_timed_event(&sequences[157], 7833, 0, EVENT_ONESHOT, stop_get_away_riser_new);
	install_timed_event(&sequences[157], 8042, 0, EVENT_ONESHOT, stop_ford_transit);
	install_timed_event(&sequences[157], 11417, 0, EVENT_ONESHOT, start_fire);
	install_timed_event(&sequences[157], 81625, 0, EVENT_ONESHOT, start_atmo_london);
	install_timed_event(&sequences[157], 89542, 0, EVENT_ONESHOT, start_after_crash);
	install_timed_event(&sequences[157], 105833, 115833, EVENT_DURATION, fade_after_crash);
	// seg438
	install_timed_event(&sequences[158], 375, 0, EVENT_ONESHOT, start_siren2);
	// seg439_a
	install_timed_event(&sequences[159], 8792, 14400, EVENT_DURATION, fade_siren);
	// seg439_b (empty)
	// seg439_c (empty)
	// seg440
	install_timed_event(&sequences[162], 42, 0, EVENT_ONESHOT, start_siren2);
	// seg441 (empty)
	// seg442 (empty)
	// seg443 (empty)
	// seg444
	install_timed_event(&sequences[166], 16208, 0, EVENT_ONESHOT, start_siren_p3);
	// seg445
	install_timed_event(&sequences[167], 16167, 18667, EVENT_DURATION, fade_siren2);
	install_timed_event(&sequences[167], 18667, 0, EVENT_ONESHOT, stop_siren);
	install_timed_event(&sequences[167], 18667, 0, EVENT_ONESHOT, stop_siren_p3);
	install_timed_event(&sequences[167], 18667, 0, EVENT_ONESHOT, stop_atmo_london);
	install_timed_event(&sequences[167], 18667, 0, EVENT_ONESHOT, stop_fire);
	// seg445_1
	install_timed_event(&sequences[168], 0, 0, EVENT_ONESHOT, start_siren_p3);
	// seg446 (empty)
	// seg447
	install_timed_event(&sequences[170], 0, 0, EVENT_ONESHOT, stop_fire);
	install_timed_event(&sequences[170], 2125, 0, EVENT_ONESHOT, start_siren_p2);
	install_timed_event(&sequences[170], 4125, 18125, EVENT_DURATION, fade_siren_p3);
	install_timed_event(&sequences[170], 18125, 0, EVENT_ONESHOT, stop_siren_p3);
	install_timed_event(&sequences[170], 21542, 0, EVENT_ONESHOT, stop_siren);
	install_timed_event(&sequences[170], 33042, 0, EVENT_ONESHOT, stop_atmo_london);
	// seg442_1 (empty)
	// EPISODE 5A
	// seg501_507
	install_timed_event(&sequences[172], 2167, 0, EVENT_ONESHOT, start_woes_resto);
	install_timed_event(&sequences[172], 2167, 8833, EVENT_DURATION, fade_after_crash2);
	install_timed_event(&sequences[172], 8833, 0, EVENT_ONESHOT, change_woes_resto);
	install_timed_event(&sequences[172], 8875, 0, EVENT_ONESHOT, start_atmo_hong_kong);
	install_timed_event(&sequences[172], 13000, 0, EVENT_ONESHOT, stop_after_crash);
	// seg508_1 (empty)
	// seg508_2
	install_timed_event(&sequences[174], 17000, 0, EVENT_ONESHOT, stop_atmo_hong_kong);
	// seg508_3
	install_timed_event(&sequences[175], 22300, 0, EVENT_ONESHOT, stop_atmo_hong_kong);
	// seg509_511
	install_timed_event(&sequences[176], 7708, 0, EVENT_ONESHOT, stop_woes_resto);
	install_timed_event(&sequences[176], 8792, 0, EVENT_ONESHOT, stop_atmo_hong_kong);
	// seg516
	install_timed_event(&sequences[177], 0, 0, EVENT_ONESHOT, start_woe_office);
	install_timed_event(&sequences[177], 13208, 0, EVENT_ONESHOT, start_woe_bowl_music);
	install_timed_event(&sequences[177], 28208, 33208, EVENT_DURATION, fade_woe_bowl_music);
	// seg517
	install_timed_event(&sequences[178], 0, 0, EVENT_ONESHOT, stop_woes_resto);
	// seg519
	install_timed_event(&sequences[179], 0, 0, EVENT_ONESHOT, start_woe_dark);
	install_timed_event(&sequences[179], 0, 4000, EVENT_DURATION, fade_woe_bowl_music2);
	install_timed_event(&sequences[179], 4000, 0, EVENT_ONESHOT, stop_woe_bowl_music);
	// seg520
	install_timed_event(&sequences[180], 0, 0, EVENT_ONESHOT, start_woe_dark_end);
	install_timed_event(&sequences[180], 0, 4000, EVENT_DURATION, fade_woe_dark);
	install_timed_event(&sequences[180], 4000, 0, EVENT_ONESHOT, stop_woe_dark);
	install_timed_event(&sequences[180], 20000, 23000, EVENT_DURATION, fade_woe_dark_end);
	install_timed_event(&sequences[180], 27583, 0, EVENT_ONESHOT, start_police_everywhere);
	install_timed_event(&sequences[180], 28292, 0, EVENT_ONESHOT, stop_woe_office);
	// seg522
	install_timed_event(&sequences[181], 0, 0, EVENT_ONESHOT, start_woe_dark_end);
	install_timed_event(&sequences[181], 0, 4000, EVENT_DURATION, fade_woe_bowl_music2);
	install_timed_event(&sequences[181], 4000, 0, EVENT_ONESHOT, stop_woe_bowl_music);
	install_timed_event(&sequences[181], 4000, 0, EVENT_ONESHOT, stop_woe_dark);
	install_timed_event(&sequences[181], 20000, 23000, EVENT_DURATION, fade_woe_dark_end);
	install_timed_event(&sequences[181], 45875, 0, EVENT_ONESHOT, start_police_everywhere);
	install_timed_event(&sequences[181], 48400, 0, EVENT_ONESHOT, stop_woe_office);
	// seg524_a
	install_timed_event(&sequences[182], 0, 0, EVENT_ONESHOT, start_hong_kong_backdoor);
	// seg524_b
	install_timed_event(&sequences[183], 42, 0, EVENT_ONESHOT, start_hong_kong_backdoor);
	// seg524_c
	install_timed_event(&sequences[184], 42, 0, EVENT_ONESHOT, start_hong_kong_backdoor);
	// seg525 (empty)
	// seg526
	install_timed_event(&sequences[186], 0, 6000, EVENT_DURATION, fade_police_everywhere);
	install_timed_event(&sequences[186], 46750, 52750, EVENT_DURATION, fade_police_everywhere2);
	// seg527 (empty)
	// seg528_a
	install_timed_event(&sequences[188], 2042, 0, EVENT_ONESHOT, start_push_your_chances);
	install_timed_event(&sequences[188], 2958, 0, EVENT_ONESHOT, stop_police_everywhere);
	install_timed_event(&sequences[188], 8625, 0, EVENT_ONESHOT, stop_hong_kong_backdoor);
	// seg528_b
	install_timed_event(&sequences[189], 19600, 0, EVENT_ONESHOT, stop_hong_kong_backdoor);
	// seg529_a
	install_timed_event(&sequences[190], 708, 4542, EVENT_DURATION, fade_police_everywhere3);
	install_timed_event(&sequences[190], 4542, 0, EVENT_ONESHOT, start_push_your_chances);
	install_timed_event(&sequences[190], 5042, 0, EVENT_ONESHOT, stop_police_everywhere);
	install_timed_event(&sequences[190], 14333, 0, EVENT_ONESHOT, stop_hong_kong_backdoor);
	// seg529_b
	install_timed_event(&sequences[191], 0, 5166, EVENT_DURATION, fade_police_everywhere4);
	install_timed_event(&sequences[191], 5167, 0, EVENT_ONESHOT, start_push_your_chances);
	install_timed_event(&sequences[191], 5292, 0, EVENT_ONESHOT, stop_police_everywhere);
	install_timed_event(&sequences[191], 15583, 0, EVENT_ONESHOT, stop_hong_kong_backdoor);
	// seg530 (empty)
	// EPISODE 5B
	// seg551
	install_timed_event(&sequences[193], 0, 0, EVENT_ONESHOT, maybe_start_police_everywhere);
	install_timed_event(&sequences[193], 0, 3500, EVENT_DURATION, fade_police_everywhere5);
	install_timed_event(&sequences[193], 12333, 21333, EVENT_DURATION, fade_police_everywhere6);
	install_timed_event(&sequences[193], 21333, 0, EVENT_ONESHOT, stop_police_everywhere);
	// seg554
	install_timed_event(&sequences[194], 0, 0, EVENT_ONESHOT, start_atmo_police_station);
	install_timed_event(&sequences[194], 0, 6000, EVENT_DURATION, fade_after_crash3);
	install_timed_event(&sequences[194], 6000, 0, EVENT_ONESHOT, stop_after_crash);
	// seg561 (empty)
	// seg555 (empty)
	// seg556_a (empty)
	// seg556_b (empty)
	// seg557 (empty)
	// seg558_a (empty)
	// seg558_b (empty)
	// seg560 (empty)
	// seg562_a (empty)
	// seg562_b (empty)
	// seg563 (empty)
	// seg564_a (empty)
	// seg564_b (empty)
	// seg565 (empty)
	// seg568_b
	install_timed_event(&sequences[209], 5750, 0, EVENT_ONESHOT, start_tenseness);
	install_timed_event(&sequences[209], 31200, 0, EVENT_ONESHOT, stop_atmo_police_station);
	// seg568_a
	install_timed_event(&sequences[210], 6708, 0, EVENT_ONESHOT, start_tenseness);
	install_timed_event(&sequences[210], 26500, 0, EVENT_ONESHOT, stop_atmo_police_station);
	// seg570_571
	install_timed_event(&sequences[211], 45125, 0, EVENT_ONESHOT, start_showdown_and_violence);
	install_timed_event(&sequences[211], 49208, 50708, EVENT_DURATION, fade_tenseness);
	install_timed_event(&sequences[211], 50708, 0, EVENT_ONESHOT, stop_tenseness);
	install_timed_event(&sequences[211], 69792, 0, EVENT_ONESHOT, start_radioplay);
	install_timed_event(&sequences[211], 69792, 0, EVENT_ONESHOT, stop_showdown_and_violence);
	// EPISODE 6A
	// seg601_602_603
	install_timed_event(&sequences[214], 0, 11000, EVENT_DURATION, fade_pushing_your_chances);
	install_timed_event(&sequences[214], 28167, 0, EVENT_ONESHOT, start_atmo_hotel_room);
	install_timed_event(&sequences[214], 39958, 0, EVENT_ONESHOT, start_atmo_tv_bg_p1);
	install_timed_event(&sequences[214], 72083, 0, EVENT_ONESHOT, start_hotel_romance);
	install_timed_event(&sequences[214], 94083, 0, EVENT_ONESHOT, start_atmo_tv_bg_trans);
	// seg604_c
	install_timed_event(&sequences[215], 1917, 0, EVENT_ONESHOT, stop_atmo_tv_bg_trans);
	install_timed_event(&sequences[215], 2917, 0, EVENT_ONESHOT, start_atmo_tv_bg_p3);
	install_timed_event(&sequences[215], 8200, 0, EVENT_ONESHOT, stop_hotel_romance);
	// seg604_d
	install_timed_event(&sequences[216], 1833, 0, EVENT_ONESHOT, stop_atmo_tv_bg_trans);
	install_timed_event(&sequences[216], 2833, 0, EVENT_ONESHOT, start_atmo_tv_bg_p3);
	install_timed_event(&sequences[216], 8167, 0, EVENT_ONESHOT, stop_hotel_romance);
	// seg605_b
	install_timed_event(&sequences[217], 2833, 0, EVENT_ONESHOT, start_on_the_news);
	// seg606 (empty)
	// seg607 (empty)
	// seg608 (empty)
	// seg610
	install_timed_event(&sequences[221], 0, 6750, EVENT_DURATION, fade_on_the_news);
	install_timed_event(&sequences[221], 6750, 0, EVENT_ONESHOT, stop_on_the_news);
	install_timed_event(&sequences[221], 6750, 0, EVENT_ONESHOT, start_tschoi_action);
	install_timed_event(&sequences[221], 13417, 0, EVENT_ONESHOT, stop_atmo_hotel_room);
	install_timed_event(&sequences[221], 13833, 0, EVENT_ONESHOT, start_atmo_stairway);
	install_timed_event(&sequences[221], 13833, 16167, EVENT_DURATION, fade_tschoi_action);
	// seg614_a (empty)
	// seg614_b (empty)
	// seg618 (empty)
	// seg615 (empty)
	// seg619 (empty)
	// seg620_621_622
	install_timed_event(&sequences[227], 15792, 0, EVENT_ONESHOT, stop_atmo_stairway);
	install_timed_event(&sequences[227], 15792, 0, EVENT_ONESHOT, start_atmo_backyard);
	// seg616_622
	install_timed_event(&sequences[228], 15042, 0, EVENT_ONESHOT, stop_atmo_stairway);
	install_timed_event(&sequences[228], 15042, 0, EVENT_ONESHOT, start_atmo_backyard);
	// seg617 (empty)
	// seg623_a
	install_timed_event(&sequences[230], 4167, 0, EVENT_ONESHOT, start_tschoi_stab);
	install_timed_event(&sequences[230], 4167, 0, EVENT_ONESHOT, stop_tschoi_action);
	install_timed_event(&sequences[230], 11800, 0, EVENT_ONESHOT, stop_atmo_backyard);
	// seg623_b
	install_timed_event(&sequences[231], 3625, 0, EVENT_ONESHOT, start_tschoi_stab);
	install_timed_event(&sequences[231], 3792, 0, EVENT_ONESHOT, stop_tschoi_action);
	install_timed_event(&sequences[231], 13800, 0, EVENT_ONESHOT, stop_atmo_backyard);
	// seg624
	install_timed_event(&sequences[232], 95, 0, EVENT_ONESHOT, start_tschoi_stab);
	install_timed_event(&sequences[232], 95, 0, EVENT_ONESHOT, stop_tschoi_action);
	install_timed_event(&sequences[232], 3958, 0, EVENT_ONESHOT, start_radioplay2);
	install_timed_event(&sequences[232], 3958, 5958, EVENT_DURATION, fade_radioplay);
	install_timed_event(&sequences[232], 7166, 0, EVENT_ONESHOT, stop_atmo_stairway);
	// seg604_a
	install_timed_event(&sequences[233], 4000, 0, EVENT_ONESHOT, stop_atmo_tv_bg_trans);
	install_timed_event(&sequences[233], 5000, 0, EVENT_ONESHOT, start_atmo_tv_bg_p2);
	install_timed_event(&sequences[233], 6083, 14083, EVENT_DURATION, fade_hotel_romance);
	install_timed_event(&sequences[233], 28333, 0, EVENT_ONESHOT, start_on_the_news2);
	install_timed_event(&sequences[233], 28333, 35958, EVENT_DURATION, fade_hotel_romance2);
	install_timed_event(&sequences[233], 35958, 0, EVENT_ONESHOT, stop_hotel_romance);
	// seg604_b
	install_timed_event(&sequences[234], 1500, 0, EVENT_ONESHOT, stop_atmo_tv_bg_trans);
	install_timed_event(&sequences[234], 2500, 0, EVENT_ONESHOT, start_atmo_tv_bg_p3);
	install_timed_event(&sequences[234], 7500, 0, EVENT_ONESHOT, stop_hotel_romance);
	// seg609_a (empty)
	// seg609_b (empty)
	// EPISODE 6B
	// seg651_1
	install_timed_event(&sequences[237], 0, 0, EVENT_ONESHOT, maybe_start_radioplay);
	install_timed_event(&sequences[237], 0, 0, EVENT_ONESHOT, start_atmo_radioplay);
	install_timed_event(&sequences[237], 12875, 0, EVENT_ONESHOT, start_thumbscrew_p1);
	install_timed_event(&sequences[237], 14000, 0, EVENT_ONESHOT, start_tchoi_hotel);
	install_timed_event(&sequences[237], 15208, 18208, EVENT_DURATION, fade_radioplay2);
	install_timed_event(&sequences[237], 18208, 0, EVENT_ONESHOT, stop_radioplay);
	// seg651_2b
	install_timed_event(&sequences[238], 27542, 0, EVENT_ONESHOT, start_knife_accent_p1);
	// seg651_2a
	install_timed_event(&sequences[239], 26375, 0, EVENT_ONESHOT, start_knife_accent_p1);
	// seg651_3 (empty)
	// seg652_a
	install_timed_event(&sequences[241], 7125, 0, EVENT_ONESHOT, start_torture_main);
	install_timed_event(&sequences[241], 7125, 13500, EVENT_DURATION, fade_thumbscrew_p1);
	install_timed_event(&sequences[241], 13500, 0, EVENT_ONESHOT, stop_thumbscrew_p1);
	// seg652_b
	install_timed_event(&sequences[242], 22708, 0, EVENT_ONESHOT, start_torture_main);
	install_timed_event(&sequences[242], 35333, 0, EVENT_ONESHOT, stop_thumbscrew_p1);
	// seg653 (empty)
	// seg654
	install_timed_event(&sequences[244], 16, 0, EVENT_ONESHOT, start_knife_accent_p2);
	// seg655_a
	install_timed_event(&sequences[245], 3583, 0, EVENT_ONESHOT, start_short_knife);
	install_timed_event(&sequences[245], 3583, 13583, EVENT_DURATION, fade_torture_main);
	install_timed_event(&sequences[245], 13583, 0, EVENT_ONESHOT, stop_torture_main);
	// seg655_b
	install_timed_event(&sequences[246], 1375, 0, EVENT_ONESHOT, start_long_knife);
	install_timed_event(&sequences[246], 1375, 11375, EVENT_DURATION, fade_torture_main2);
	install_timed_event(&sequences[246], 11375, 0, EVENT_ONESHOT, stop_torture_main);
	// seg655_c
	install_timed_event(&sequences[247], 4917, 0, EVENT_ONESHOT, start_long_knife);
	install_timed_event(&sequences[247], 4917, 14917, EVENT_DURATION, fade_torture_main3);
	install_timed_event(&sequences[247], 14917, 0, EVENT_ONESHOT, stop_torture_main);
	// seg656 (empty)
	// seg666_a
	install_timed_event(&sequences[249], 0, 0, EVENT_ONESHOT, stop_short_knife);
	install_timed_event(&sequences[249], 0, 0, EVENT_ONESHOT, stop_long_knife);
	install_timed_event(&sequences[249], 0, 0, EVENT_ONESHOT, start_thumbscrew_talk);
	install_timed_event(&sequences[249], 0, 6000, EVENT_DURATION, fade_thumbscrew_p2);
	install_timed_event(&sequences[249], 6000, 0, EVENT_ONESHOT, stop_thumbscrew_p2);
	// seg657
	install_timed_event(&sequences[250], 23042, 0, EVENT_ONESHOT, start_torture_tom);
	install_timed_event(&sequences[250], 23500, 0, EVENT_ONESHOT, stop_short_knife);
	install_timed_event(&sequences[250], 23500, 0, EVENT_ONESHOT, stop_long_knife);
	install_timed_event(&sequences[250], 25917, 0, EVENT_ONESHOT, start_thumbscrew_p2);
	// seg660 (empty)
	// seg667_669_670_a
	install_timed_event(&sequences[252], 0, 0, EVENT_ONESHOT, start_thumbscrew_angry);
	install_timed_event(&sequences[252], 0, 5000, EVENT_DURATION, fade_thumbscrew_p2_2);
	install_timed_event(&sequences[252], 5000, 0, EVENT_ONESHOT, stop_thumbscrew_p2);
	// seg667_669_670_b
	install_timed_event(&sequences[253], 0, 0, EVENT_ONESHOT, start_thumbscrew_angry2);
	install_timed_event(&sequences[253], 0, 5000, EVENT_DURATION, fade_thumbscrew_p2_2);
	install_timed_event(&sequences[253], 5000, 0, EVENT_ONESHOT, stop_thumbscrew_p2);
	// seg673
	install_timed_event(&sequences[254], 15875, 0, EVENT_ONESHOT, start_torture_end);
	// seg671_a
	install_timed_event(&sequences[255], 14208, 0, EVENT_ONESHOT, start_torture_end);
	// seg671_b
	install_timed_event(&sequences[256], 14208, 0, EVENT_ONESHOT, start_torture_end);
	// seg672
	install_timed_event(&sequences[257], 13792, 0, EVENT_ONESHOT, start_matt_alone);
	install_timed_event(&sequences[257], 37542, 41000, EVENT_DURATION, fade_matt_alone);
	install_timed_event(&sequences[257], 41000, 0, EVENT_ONESHOT, stop_tchoi_hotel);
	// seg661 (empty)
	// seg674
	install_timed_event(&sequences[259], 33583, 0, EVENT_ONESHOT, start_matt_alone2);
	install_timed_event(&sequences[259], 33583, 39208, EVENT_DURATION, fade_torture_end);
	install_timed_event(&sequences[259], 39208, 0, EVENT_ONESHOT, stop_torture_end);
	install_timed_event(&sequences[259], 63000, 0, EVENT_ONESHOT, stop_tchoi_hotel);
	// seg675
	install_timed_event(&sequences[260], 333, 1333, EVENT_DURATION, fade_torture_end2);
	// seg662
	install_timed_event(&sequences[261], 458, 0, EVENT_ONESHOT, start_hoelzli_accent);
	// seg666_b
	install_timed_event(&sequences[262], 0, 0, EVENT_ONESHOT, start_thumbscrew_talk);
	install_timed_event(&sequences[262], 0, 6000, EVENT_DURATION, fade_thumbscrew_p2);
	install_timed_event(&sequences[262], 6000, 0, EVENT_ONESHOT, stop_thumbscrew_p2);
	// seg663 (empty)
	// seg664 (empty)
	// seg665
	install_timed_event(&sequences[265], 0, 0, EVENT_ONESHOT, start_thumbscrew_angry2);
	install_timed_event(&sequences[265], 0, 5000, EVENT_DURATION, fade_thumbscrew_p2_2);
	install_timed_event(&sequences[265], 5000, 0, EVENT_ONESHOT, stop_thumbscrew_p2);
	// seg666_c
	install_timed_event(&sequences[266], 0, 0, EVENT_ONESHOT, start_thumbscrew_talk);
	install_timed_event(&sequences[266], 0, 6000, EVENT_DURATION, fade_thumbscrew_p2);
	install_timed_event(&sequences[266], 6000, 0, EVENT_ONESHOT, stop_thumbscrew_p2);
	// seg668_669_670_a (empty)
	// seg668_669_670_b (empty)
	// EPISODE 7
	// seg732
	install_timed_event(&sequences[269], 0, 0, EVENT_ONESHOT, maybe_start_matt_alone);
	install_timed_event(&sequences[269], 41625, 0, EVENT_ONESHOT, start_atmo_tunnel);
	install_timed_event(&sequences[269], 60417, 0, EVENT_ONESHOT, stop_atmo_tunnel);
	install_timed_event(&sequences[269], 60458, 0, EVENT_ONESHOT, start_drum_and_bass);
	install_timed_event(&sequences[269], 60458, 69458, EVENT_DURATION, fade_drum_and_bass);
	// seg701
	install_timed_event(&sequences[270], 0, 0, EVENT_ONESHOT, start_atmo_police_several_sirens);
	install_timed_event(&sequences[270], 42, 0, EVENT_ONESHOT, start_atmo_train_p4_rear);
	install_timed_event(&sequences[270], 21417, 0, EVENT_ONESHOT, start_atmo_train_p5_bass);
	install_timed_event(&sequences[270], 21417, 0, EVENT_ONESHOT, start_forged);
	install_timed_event(&sequences[270], 26375, 0, EVENT_ONESHOT, start_atmo_tunnel);
	install_timed_event(&sequences[270], 26500, 0, EVENT_ONESHOT, change_atmo_train_p5_bass);
	install_timed_event(&sequences[270], 38750, 0, EVENT_ONESHOT, start_atmo_train_p1_longer);
	install_timed_event(&sequences[270], 63625, 0, EVENT_ONESHOT, start_atmo_train_p4_short);
	// seg702 (empty)
	// seg707
	install_timed_event(&sequences[272], 12583, 0, EVENT_ONESHOT, start_mayling_truth);
	install_timed_event(&sequences[272], 14958, 21958, EVENT_DURATION, fade_forged);
	install_timed_event(&sequences[272], 21958, 0, EVENT_ONESHOT, stop_forged);
	install_timed_event(&sequences[272], 38958, 0, EVENT_ONESHOT, start_atmo_train_p4);
	install_timed_event(&sequences[272], 52792, 0, EVENT_ONESHOT, start_atmo_train_p1);
	// seg703
	install_timed_event(&sequences[273], 14375, 0, EVENT_ONESHOT, start_atmo_train_p2);
	// seg704
	install_timed_event(&sequences[274], 8375, 0, EVENT_ONESHOT, start_atmo_train_p6);
	// seg708 (empty)
	// seg709 (empty)
	// seg710 (empty)
	// seg711 (empty)
	// seg712
	install_timed_event(&sequences[279], 10333, 0, EVENT_ONESHOT, start_atmo_train_p4_longer);
	install_timed_event(&sequences[279], 18625, 24625, EVENT_DURATION, fade_mayling_truth);
	install_timed_event(&sequences[279], 24625, 0, EVENT_ONESHOT, stop_mayling_truth);
	// seg713_a
	install_timed_event(&sequences[280], 3083, 0, EVENT_ONESHOT, start_atmo_police_single_siren_short);
	// seg713_b
	install_timed_event(&sequences[281], 4958, 0, EVENT_ONESHOT, start_atmo_police_single_siren_short2);
	// seg713_c
	install_timed_event(&sequences[282], 4167, 0, EVENT_ONESHOT, start_atmo_police_single_siren_short2);
	// seg714_723
	install_timed_event(&sequences[283], 18625, 0, EVENT_ONESHOT, start_atmo_train_p4_2);
	install_timed_event(&sequences[283], 22875, 0, EVENT_ONESHOT, change_atmo_train_p4);
	// seg724
	install_timed_event(&sequences[284], 18625, 0, EVENT_ONESHOT, start_police_everywhere_p1);
	install_timed_event(&sequences[284], 19583, 0, EVENT_ONESHOT, start_atmo_train_p6_2);
	install_timed_event(&sequences[284], 26208, 0, EVENT_ONESHOT, start_atmo_police_single_siren_2_short);
	install_timed_event(&sequences[284], 30375, 0, EVENT_ONESHOT, stop_atmo_tunnel);
	install_timed_event(&sequences[284], 51833, 0, EVENT_ONESHOT, start_drum_and_bass);
	install_timed_event(&sequences[284], 53250, 0, EVENT_ONESHOT, start_revellers_p1);
	install_timed_event(&sequences[284], 53250, 60833, EVENT_DURATION, fade_drum_and_bass2);
	install_timed_event(&sequences[284], 61833, 0, EVENT_ONESHOT, stop_police_everywhere_p1);
	// seg760
	install_timed_event(&sequences[285], 0, 0, EVENT_ONESHOT, start_revellers_p2);
	// seg761
	install_timed_event(&sequences[286], 0, 0, EVENT_ONESHOT, start_revellers_p3);
	// seg762 (empty)
	// seg763 (empty)
	// seg764
	install_timed_event(&sequences[289], 0, 0, EVENT_ONESHOT, start_auction_guy2);
	install_timed_event(&sequences[289], 0, 0, EVENT_ONESHOT, start_atmo_tunnel);
	install_timed_event(&sequences[289], 0, 10958, EVENT_DURATION, fade_drum_and_bass3);
	install_timed_event(&sequences[289], 10958, 0, EVENT_ONESHOT, start_atmo_train_p5);
	install_timed_event(&sequences[289], 13000, 0, EVENT_ONESHOT, stop_drum_and_bass);
	install_timed_event(&sequences[289], 15250, 18250, EVENT_DURATION, fade_atmo_train_p5);
	install_timed_event(&sequences[289], 18542, 0, EVENT_ONESHOT, start_atmo_train_p1_2);
	// seg725_k (empty)
	// seg727
	install_timed_event(&sequences[291], 4167, 0, EVENT_ONESHOT, start_police_everywhere_p2);
	install_timed_event(&sequences[291], 4167, 8333, EVENT_DURATION, fade_auction_guy);
	install_timed_event(&sequences[291], 8333, 0, EVENT_ONESHOT, stop_auction_guy);
	install_timed_event(&sequences[291], 53708, 0, EVENT_ONESHOT, stop_atmo_tunnel);
	// seg734
	install_timed_event(&sequences[292], 0, 0, EVENT_ONESHOT, start_revellers_p5);
	install_timed_event(&sequences[292], 2500, 0, EVENT_ONESHOT, stop_mayling_truth);
	install_timed_event(&sequences[292], 2500, 0, EVENT_ONESHOT, stop_forged);
	install_timed_event(&sequences[292], 3750, 0, EVENT_ONESHOT, change_revellers_p5);
	install_timed_event(&sequences[292], 10750, 0, EVENT_ONESHOT, stop_matt_alone);
	// seg738 (empty)
	// seg739_2
	install_timed_event(&sequences[294], 12000, 0, EVENT_ONESHOT, stop_revellers_p5);
	// seg739_1
	install_timed_event(&sequences[295], 15458, 0, EVENT_ONESHOT, stop_revellers_p5);
	// seg739_a
	install_timed_event(&sequences[296], 8250, 0, EVENT_ONESHOT, start_after_fight);
	install_timed_event(&sequences[296], 8250, 12292, EVENT_DURATION, fade_drum_and_bass4);
	install_timed_event(&sequences[296], 12292, 0, EVENT_ONESHOT, stop_drum_and_bass);
	// seg739_b
	install_timed_event(&sequences[297], 8167, 0, EVENT_ONESHOT, start_after_fight_trans);
	install_timed_event(&sequences[297], 8167, 12167, EVENT_DURATION, fade_drum_and_bass5);
	install_timed_event(&sequences[297], 12167, 0, EVENT_ONESHOT, stop_drum_and_bass);
	// seg733
	install_timed_event(&sequences[298], 0, 0, EVENT_ONESHOT, stop_atmo_tunnel);
	install_timed_event(&sequences[298], 11667, 0, EVENT_ONESHOT, start_drum_and_bass);
	install_timed_event(&sequences[298], 11667, 20667, EVENT_DURATION, fade_drum_and_bass6);
	// seg715
	install_timed_event(&sequences[299], 5583, 0, EVENT_ONESHOT, start_atmo_train_p5_longer);
	// seg717_720
	install_timed_event(&sequences[300], 13292, 0, EVENT_ONESHOT, start_atmo_police_single_siren_short3);
	install_timed_event(&sequences[300], 15875, 0, EVENT_ONESHOT, start_atmo_train_p6_2);
	// seg717_718
	install_timed_event(&sequences[301], 13250, 0, EVENT_ONESHOT, start_atmo_police_single_siren_short);
	// seg719_720
	install_timed_event(&sequences[302], 2000, 0, EVENT_ONESHOT, start_atmo_train_p6_2);
	// seg716_723
	install_timed_event(&sequences[303], 2000, 0, EVENT_ONESHOT, start_atmo_train_p4_3);
	install_timed_event(&sequences[303], 12958, 0, EVENT_ONESHOT, change_atmo_train_p4_2);
	install_timed_event(&sequences[303], 27500, 0, EVENT_ONESHOT, stop_mayling_truth);
	// seg721_723
	install_timed_event(&sequences[304], 21375, 0, EVENT_ONESHOT, start_atmo_train_p4_4);
	install_timed_event(&sequences[304], 25625, 0, EVENT_ONESHOT, change_atmo_train_p4_2);
	install_timed_event(&sequences[304], 40208, 0, EVENT_ONESHOT, stop_mayling_truth);
	// seg737 (empty)
	// seg738 (empty)
	// seg740
	install_timed_event(&sequences[307], 14671, 23000, EVENT_DURATION, fade_revellers_p5);
	install_timed_event(&sequences[307], 23000, 0, EVENT_ONESHOT, stop_revellers_p5);
	// seg741
	install_timed_event(&sequences[308], 14083, 21000, EVENT_DURATION, fade_revellers_p5_2);
	install_timed_event(&sequences[308], 21000, 0, EVENT_ONESHOT, stop_revellers_p5);
	// seg742
	install_timed_event(&sequences[309], 0, 0, EVENT_ONESHOT, start_auction_guy2);
	install_timed_event(&sequences[309], 0, 12875, EVENT_DURATION, fade_drum_and_bass7);
	install_timed_event(&sequences[309], 12875, 0, EVENT_ONESHOT, start_atmo_train_p5_2);
	install_timed_event(&sequences[309], 13000, 0, EVENT_ONESHOT, stop_drum_and_bass);
	install_timed_event(&sequences[309], 16125, 0, EVENT_ONESHOT, start_atmo_train_p1_3);
	// seg743_k (empty)
	// seg743_1 (empty)
	// seg745
	install_timed_event(&sequences[312], 0, 0, EVENT_ONESHOT, start_police_everywhere_p2_2);
	install_timed_event(&sequences[312], 0, 4000, EVENT_DURATION, fade_auction_guy2);
	install_timed_event(&sequences[312], 4000, 0, EVENT_ONESHOT, stop_auction_guy);
	// seg747_2_749_750
	install_timed_event(&sequences[313], 12042, 0, EVENT_ONESHOT, start_police_everywhere_p2_3);
	install_timed_event(&sequences[313], 12042, 16042, EVENT_DURATION, fade_auction_guy3);
	install_timed_event(&sequences[313], 16042, 0, EVENT_ONESHOT, stop_auction_guy);
	// seg765_756_757
	install_timed_event(&sequences[314], 0, 0, EVENT_ONESHOT, start_revellers_p4);
	install_timed_event(&sequences[314], 26708, 31292, EVENT_DURATION, fade_drum_and_bass8);
	install_timed_event(&sequences[314], 31292, 0, EVENT_ONESHOT, stop_drum_and_bass);
	install_timed_event(&sequences[314], 31292, 0, EVENT_ONESHOT, start_after_fight);
	// seg770
	install_timed_event(&sequences[315], 0, 0, EVENT_ONESHOT, stop_atmo_train_p1);
	install_timed_event(&sequences[315], 3458, 0, EVENT_ONESHOT, maybe_start_intentness_mood);
	install_timed_event(&sequences[315], 3458, 10458, EVENT_DURATION, fade_intentness_mood);
	// seg770_2 (empty)
	// EPISODE 9A
	// seg901_1_901_2
	// seg902_b
	// seg902_a
	// seg903_a
	// seg903_b
	// seg904_a
	// seg904_b_905_1
	// seg906_a
	// seg906_b
	// seg907_1
	// seg946_1
	// seg905_2
	// seg907_2
	// seg908_a_909_913
	// seg908_c
	// seg908_b
	// seg910
	// seg912_913
	// seg915
	// seg916
	// seg917_b
	// seg917_a
	// seg918
	// seg919
	// seg920
	// seg914
	// seg911_913
	// seg947_1_913
	// seg948_1
	// seg921
	// seg922
	// seg923
	// seg924
	// seg927
	// seg928
	// seg928_939
	// seg929
	// seg930
	// seg930_939
	// seg931_933_934_a_935
	// seg929_939
	// seg933_2_937_a_938
	// seg936
	// seg937_a_938
	// seg937_b_938
	// seg939
	// seg945
	// EPISODE 9B
	// seg951_1_951_2
	// seg952_b
	// seg952_a
	// seg953_a
	// seg953_b
	// seg954_a
	// seg954_b
	// seg955
	// seg956_a_947_2
	// seg956_b
	// seg957_1
	// seg946_2_947_2
	// seg948_2
	// seg958_a_959
	// seg958_c
	// seg958_b
	// seg957_2
	// seg960
	// seg961
	// seg962
	// seg963
	// seg964
	// seg965
	// seg966_b
	// seg966_a
	// seg967
	// seg968
	// seg969_a
	// seg969_b
	// seg970
	// seg970_2
	// seg970_1
	// seg971_b
	// seg971_a
	// seg974_1
	// seg974
	// seg975
	install_timed_event(&sequences[400], 18375, 0, EVENT_ONESHOT, dont_know_trojan_jump);
	// seg976
	// seg973_b
	// seg973_a
	// seg972
	// seg977_978
	// seg990_991_992
	// seg990_992
	// seg994
	// seg988_984_2
	// seg974_2
	// seg977_979
	// EPISODE 10
	// EPISODE 11
}

void fill_sequences() {
	// Creating sequences links
	// OPENING
	fill_sequence("seg101", &sequences[0], seg102_a, selfless, selfish, NULL, seg102_a, seg102_b, NULL, 74583, 80250, 76875); // seg101
	fill_sequence("seg102_a", &sequences[1], seg106, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg102_a
	fill_sequence("seg102_b", &sequences[2], seg106, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg102_b
	fill_sequence("seg106", &sequences[3], seg107_a, board, help, NULL, seg107_a, seg107_b, NULL, 18625, 23125, 22375); // seg106
	fill_sequence("seg107_a", &sequences[4], seg109_110_b_111, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg107a
	fill_sequence("seg107_b", &sequences[5], seg109_110_b_111, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg107b
	// EPISODE 1
	fill_sequence("seg109_110_b_111", &sequences[6], seg112_1, yes, no, why, seg113_116, seg114, seg115, 213625, 219125, 217792); // seg109_110_b_111
	fill_sequence("seg113_116", &sequences[7], seg115, okay, not_good_enough, NULL, seg117, seg115, NULL, 15500, 20000, 15500); // seg113_116
	fill_sequence("seg114", &sequences[8], seg121, no, okay, why_at_all, seg121, seg117, seg115, 16667, 21208, 16667); // seg114
	fill_sequence("seg115", &sequences[9], seg121, ok, two_hundred, forget_it, seg117, seg118, seg121, 29375, 33875, 29375); // seg115
	fill_sequence("seg121", &sequences[10], seg122_a_122_b, ignore, check_cctv, NULL, seg122_a_122_b, seg123, NULL, 9917, 14417, 12792); // seg121
	fill_sequence("seg118", &sequences[11], seg120, deal, three_hundred, NULL, seg119, seg120, NULL, 2458, 6958, 2458); // seg118
	fill_sequence("seg119", &sequences[12], seg128, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg119
	fill_sequence("seg117", &sequences[13], seg128, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg117
	fill_sequence("seg128", &sequences[14], seg129, nevermind, check_cctv, NULL, seg129, seg123, NULL, 7208, 11708, 9750); // seg128
	fill_sequence("seg129", &sequences[15], seg133_swipe, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg129
	fill_sequence("seg122_a_122_b", &sequences[16], seg126, go_check, call_police, NULL, seg127, seg126, NULL, 38458, 42458, 42458); // seg122_a_122_b
	fill_sequence("seg136", &sequences[17], seg137, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg136
	fill_sequence("seg141", &sequences[18], seg144, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg141
	fill_sequence("seg139", &sequences[19], seg138_a_138_b, okay, no, NULL, seg138_a_138_b, seg140, NULL, 8375, 11875, 10333); // seg139
	fill_sequence("seg137", &sequences[20], eval_has_pepper_def, okay, text_has_pepper, NULL, seg138_a_138_b, eval_has_pepper, NULL, 24792, 29000, 27958); // seg137
	fill_sequence("seg138_a_138_b", &sequences[21], seg144, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg138_a_138_b
	fill_sequence("seg133_k", &sequences[22], seg134_2, call_police, go_there, take_pepper_spray, seg136, seg134_2, seg134_1, 1417, 5417, 1417); // seg133_swipe
	fill_sequence("seg134_1", &sequences[23], seg137, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0);  // seg134_1
	fill_sequence("seg120", &sequences[24], seg121, okay, forget_it, NULL, seg119, seg121, NULL, 19917, 24417, 19917); // seg120
	fill_sequence("seg140", &sequences[25], seg138_a_138_b, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg140
	fill_sequence("seg123", &sequences[26], seg123_tap_130_tap, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg123
	fill_sequence("seg123_130_k", &sequences[27], eval_cctv_seg, all_clear, go_check, NULL, eval_cctv_seg, seg125, NULL, 5000, 9542, 5000); // seg123_tap_130_tap
	fill_sequence("seg135", &sequences[28], seg143, keep_pepper_spray, drop_it, NULL, seg142, seg143, NULL, 32542, 35542, 35542); // seg135
	fill_sequence("seg127", &sequences[29], seg135, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg127
	fill_sequence("seg142", &sequences[30], seg143, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg142
	fill_sequence("seg143", &sequences[31], seg144, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg143
	fill_sequence("seg144", &sequences[32], seg145_swipe, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg144
	fill_sequence("seg145_k", &sequences[33], seg148_b, drive, run, NULL, seg148_b, seg146_a, NULL, 2000, 6542, 2000); // seg145_swipe
	fill_sequence("seg148_b", &sequences[34], seg201, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg148_b (END OF EPISODE -> 02)
	fill_sequence("seg146_a", &sequences[35], seg147_a_148_a, turn_back, keep_going, NULL, seg147_a_148_a, seg147_b, NULL, 7625, 12000, 11625); // seg146_a
	fill_sequence("seg147_a_148_a", &sequences[36], seg148_b, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg147_a_148_a
	fill_sequence("seg147_b", &sequences[37], seg202, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg147_b (END OF EPISODE -> 02)
	fill_sequence("seg126", &sequences[38], seg135, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg126
	fill_sequence("seg134_2", &sequences[39], seg137, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg134_2
	fill_sequence("seg125", &sequences[40], seg135, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg125
	fill_sequence("seg112_1", &sequences[212], seg112_2_122_b, yes, no, NULL, seg113_116, seg114, NULL, 7625, 11750, 8208); // seg112_1
	fill_sequence("seg112_2_122_b", &sequences[213], seg126, go_check, call_police, NULL, seg127, seg126, NULL, 22833, 26833, 26833); // seg112_2_122_b
	// EPISODE 2
	fill_sequence("seg201", &sequences[41], seg206, no, do_it, NULL, seg203, seg206, NULL, 30375, 34917, 32667); // seg201
	fill_sequence("seg202", &sequences[42], seg207, okay, no, NULL, seg207, seg202_1, NULL, 17583, 19958, 21333); // seg202
	fill_sequence("seg203", &sequences[43], seg205, go, no_go, NULL, seg204, seg205, NULL, 12667, 17208, 14417); // seg203
	fill_sequence("seg204", &sequences[44], seg212, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg204
	fill_sequence("seg205", &sequences[45], seg212, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg205
	fill_sequence("seg206", &sequences[46], seg212, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg206
	fill_sequence("seg207", &sequences[47], seg208_213_214, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg207
	fill_sequence("seg202_1", &sequences[48], seg210, do_it, leg_it, NULL, seg210, seg209, NULL, 6875, 11458, 11458); // seg202_1
	fill_sequence("seg209", &sequences[49], seg208_213_214, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg209
	fill_sequence("seg210", &sequences[50], seg208_213_214, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg210
	fill_sequence("seg208_213_214", &sequences[51], seg215, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg208_213_214
	fill_sequence("seg215", &sequences[52], seg217, contradict, play_cool, NULL, seg216, seg217, NULL, 34792, 38833, 35958); // seg215
	fill_sequence("seg216", &sequences[53], seg217, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg216
	fill_sequence("seg217", &sequences[54], seg219, protest, steal_away, NULL, seg218, seg219, NULL, 5375, 8917, 8917); // seg217
	fill_sequence("seg218", &sequences[55], seg223, protest, hold_still, NULL, seg220_1, seg223, NULL, 5083, 8625, 7833); // seg218
	fill_sequence("seg219", &sequences[56], seg223, stay_calm, make_suggestion, NULL, seg223, seg224, NULL, 8542, 12667, 12667); // seg219
	fill_sequence("seg220_1", &sequences[57], seg220_2, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg220_1
	fill_sequence("seg220_2", &sequences[58], seg230, okay, whats_in, no_way, seg230, seg228, seg227, 20625, 25167, 22792); // seg220_2
	fill_sequence("seg223", &sequences[59], seg220_2, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg223
	fill_sequence("seg224", &sequences[60], seg225, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg224
	fill_sequence("seg225", &sequences[61], seg226_1, push_it, okay, NULL, seg231, seg226_1, NULL, 27708, 31333, 30083); // seg225
	fill_sequence("seg226_1", &sequences[62], seg226, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg226_1
	fill_sequence("seg226", &sequences[63], seg301_1_301_2, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg226 (END OF EPISODE -> 03)
	fill_sequence("seg212", &sequences[64], seg215, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg212
	fill_sequence("seg230", &sequences[65], seg226, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg230
	fill_sequence("seg228", &sequences[66], seg230, okay, push_it, NULL, seg230, eval_coming_from_seg223, NULL, 4833, 8500, 7292); // seg228
	fill_sequence("seg229", &sequences[67], seg230, fair_enough, keep_pushing, NULL, seg230, seg231, NULL, 6292, 9875, 8708); // seg229
	fill_sequence("seg227", &sequences[68], seg226, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg227
	fill_sequence("seg231", &sequences[69], seg301_1_301_2, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg231 (END OF EPISODE -> 03)
	// EPISODE 3
	fill_sequence("seg301_1_301_2", &sequences[70], seg302_a, agree, disagree, NULL, seg302_a, seg302_b, NULL, 99542, 102583, 102583); // seg301_1_301_2
	fill_sequence("seg302_a", &sequences[71], seg303_310, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg302_a
	fill_sequence("seg302_b", &sequences[72], seg303_310, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg302_b
	fill_sequence("seg303_310", &sequences[73], seg312, let_her, intervene, NULL, seg311, seg312, NULL, 192458, 197000, 197000); // seg303_310
	fill_sequence("seg311", &sequences[74], seg313, let_her, intervene, NULL, seg313, seg314_2, NULL, 70667, 75625, 73417); // seg311
	fill_sequence("seg312", &sequences[75], seg315, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg312
	fill_sequence("seg314_1", &sequences[76], seg314, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg314_1
	fill_sequence("seg314_2", &sequences[77], seg314, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg314_2
	fill_sequence("seg313", &sequences[78], seg315, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg313
	fill_sequence("seg315", &sequences[79], eval_intervened, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg315
	fill_sequence("seg316_b", &sequences[80], seg318, prevent, do_as_told, NULL, seg317, seg318, NULL, 10125, 14375, 14375); // seg316_b
	fill_sequence("seg316_c", &sequences[81], seg318, prevent, do_as_told, NULL, seg317, seg318, NULL, 10208, 14458, 14458); // seg316_c
	fill_sequence("seg317", &sequences[82], seg318, up, down, NULL, seg319, seg318, NULL, 9750, 14292, 12083); // seg317
	fill_sequence("seg318", &sequences[83], eval_intervened2, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg318
	fill_sequence("seg343_344_a", &sequences[84], seg345, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg343_344_a
	fill_sequence("seg343_344_b", &sequences[85], seg345, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg343_344_b
	fill_sequence("seg314", &sequences[86], seg315, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg314
	fill_sequence("seg345", &sequences[87], seg349_355_356, guard, play_along, NULL, seg346_350_352, seg349_355_356, NULL, 31667, 36208, 36208); // seg345
	fill_sequence("seg319", &sequences[88], seg320_swipe, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg319
	fill_sequence("seg320_k", &sequences[89], seg322, enter_offices, go_downstairs, NULL, seg322, seg321_324, NULL, 542, 9542, 542); // seg320_swipe
	fill_sequence("seg322", &sequences[90], seg322_tap, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg322
	fill_sequence("seg322_tap", &sequences[91], seg326_324, alert_staff, make_call, NULL, seg326_324, seg327, NULL, 833, 7500, 833); // seg322_tap
	fill_sequence("seg326_324", &sequences[92], seg325_b, squeal, keep_quiet, NULL, seg325_a, seg325_b, NULL, 31583, 35333, 35333); // seg326_324
	fill_sequence("seg327", &sequences[93], seg329, explain, lie, dial_999, seg328, seg329, seg334, 10167, 14208, 14208); // seg327
	fill_sequence("seg328", &sequences[94], seg330, squeal, give_hint, NULL, seg333, seg330, NULL, 10333, 20333, 20333); // seg328
	fill_sequence("seg329", &sequences[95], seg329_1, squeal, keep_quiet, NULL, seg333, seg329_1, NULL, 16708, 21208, 21208); // seg329
	fill_sequence("seg329_1", &sequences[96], seg331, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg329_1
	fill_sequence("seg331", &sequences[97], seg335, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg331
	fill_sequence("seg333", &sequences[98], seg331, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg333
	fill_sequence("seg346_350_352", &sequences[99], seg360, let_it_be, pick_it_up, NULL, seg360, seg354, NULL, 60000, 65250, 64750); // seg346_350_352
	fill_sequence("seg354", &sequences[100], seg363, all_clear, warning, NULL, seg363, seg365_366_double, NULL, 3542, 7667, 5708); // seg354
	fill_sequence("seg365_366", &sequences[101], seg342, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg365_366
	fill_sequence("seg342", &sequences[102], eval_ep4_start, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg342 (END OF EPISODE -> 04)
	fill_sequence("seg335", &sequences[103], eval_security_alert, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg335
	fill_sequence("seg341", &sequences[104], seg342, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg341
	fill_sequence("seg338", &sequences[105], seg340, ignore, answer, NULL, seg340, seg339, NULL, 6917, 10292, 9667); // seg338
	fill_sequence("seg339", &sequences[106], seg340, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg339
	fill_sequence("seg340", &sequences[107], eval_ep4_start, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg340 (END OF EPISODE -> 04)
	fill_sequence("seg330", &sequences[108], seg335, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg330
	fill_sequence("seg349_355_356", &sequences[109], seg358_359, dont, _do, NULL, seg358_359, seg357, NULL, 31667, 36208, 36208); // seg349_355_356
	fill_sequence("seg357", &sequences[110], seg358_359, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg357
	fill_sequence("seg358_359", &sequences[111], eval_sabotage, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg358_359
	fill_sequence("seg364_367_a_368", &sequences[112], seg369_1k, enter_correct_key, enter_wrong_key, NULL, seg369_1k, seg369_2k, NULL, 20125, 24542, 24542); // seg364_367_a_368
	fill_sequence("seg364_367_b_368", &sequences[113], seg369_1k, enter_correct_key, enter_wrong_key, NULL, seg369_1k, seg369_2k, NULL, 17250, 21958, 21958); // seg364_367_b_368
	fill_sequence("seg321_324", &sequences[114], seg325_b, squeal, keep_quiet, NULL, seg325_a, seg325_b, NULL, 34125, 37875, 37875); // seg321_324
	fill_sequence("seg325_a", &sequences[115], seg335, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg325_a
	fill_sequence("seg325_b", &sequences[116], seg335, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg325_b
	fill_sequence("seg334", &sequences[117], seg336, keep_quiet, squeal, NULL, seg336, seg337, NULL, 16875, 20625, 20625); // seg334
	fill_sequence("seg336", &sequences[118], seg331, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg336
	fill_sequence("seg337", &sequences[119], seg331, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg337
	fill_sequence("seg360", &sequences[120], seg361, let_it_be, pick_it_up, NULL, seg362, seg361, NULL, 4375, 8917, 8917); // seg360
	fill_sequence("seg361", &sequences[121], seg363, all_clear, warning, NULL, seg363, seg365_366, NULL, 2875, 7000, 7000); // seg361
	fill_sequence("seg362", &sequences[122], eval_sabotage, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg362
	fill_sequence("seg363", &sequences[123], eval_sabotage, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg363
	fill_sequence("seg369_1k", &sequences[124], seg370_375, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg369_1k
	fill_sequence("seg369_2k", &sequences[125], seg373_374_366, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg369_2k
	fill_sequence("seg370_375", &sequences[126], eval_ep4_start, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg370_375 (END OF EPISODE -> 04)
	fill_sequence("seg373_374_366", &sequences[127], seg342, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg373_374_366
	// EPISODE 4
	fill_sequence("seg415_418", &sequences[128], seg417_b, keep_quiet, speak_up, NULL, seg417_b, seg419, NULL, 20917, 25417, 25417); // seg415_418
	fill_sequence("seg415_416", &sequences[129], seg417_b, speak_up, keep_quiet, NULL, seg417_a, seg417_b, NULL, 18875, 23417, 23417); // seg415_416
	fill_sequence("seg402", &sequences[130], seg403_b, speak_up, keep_quiet, NULL, seg403_a, seg403_b, NULL, 28375, 29500, 29500); // seg402
	fill_sequence("seg406", &sequences[131], eval_low_sabotage, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg406
	fill_sequence("seg407_a", &sequences[132], seg410, high_five, refuse, NULL, seg408, seg410, NULL, 12000, 15958, 15958); // seg407_a
	fill_sequence("seg407_b", &sequences[133], seg412, smile, disagree, NULL, seg407_c, seg412, NULL, 10417, 14958, 14958); // seg407_b
	fill_sequence("seg408", &sequences[134], seg410, right, not_at_all, NULL, seg409, seg410, NULL, 12375, 16500, 15958); // seg408
	fill_sequence("seg403_a", &sequences[135], seg404_a, disagree, take_the_point, NULL, seg404_a, seg404_b, NULL, 13875, 17917, 14417); // seg403_a
	fill_sequence("seg403_b", &sequences[136], seg411_a, reply, keep_quiet, NULL, seg405, seg411_a, NULL, 17625, 22125, 19458); // seg403_b
	fill_sequence("seg404_a", &sequences[137], seg414, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg404_a
	fill_sequence("seg404_b", &sequences[138], seg414, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg404_b
	fill_sequence("seg407_c", &sequences[139], seg410, high_five, refuse, NULL, seg408, seg410, NULL, 4042, 8000, 8000); // seg407_c
	fill_sequence("seg409", &sequences[140], seg414, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg409
	fill_sequence("seg410", &sequences[141], seg411_a, keep_quiet, reply, NULL, seg411_a, seg411_b, NULL, 21542, 26083, 25583); // seg410
	fill_sequence("seg411_a", &sequences[142], seg414, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg411_a
	fill_sequence("seg411_b", &sequences[143], seg414, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg411_b
	fill_sequence("seg412", &sequences[144], seg410, dont_go_there, reply, NULL, seg410, seg413, NULL, 4833, 9375, 9375); // seg412
	fill_sequence("seg413", &sequences[145], seg414, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg413
	fill_sequence("seg417_a", &sequences[146], seg420, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg417_a
	fill_sequence("seg417_b", &sequences[147], seg420, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg417_b
	fill_sequence("seg405", &sequences[148], seg414, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg405
	fill_sequence("seg419", &sequences[149], seg420, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg419
	fill_sequence("seg414", &sequences[150], seg434, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg414
	fill_sequence("seg420", &sequences[151], seg421_a, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg420
	fill_sequence("seg421_a", &sequences[152], seg434, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg421_a
	fill_sequence("seg434", &sequences[153], seg435_c, speak_up, keep_quiet, NULL, seg435_b, seg435_c, NULL, 32042, 36542, 35333); // seg434
	fill_sequence("seg435_a", &sequences[154], seg436_437, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg435_a
	fill_sequence("seg435_b", &sequences[155], seg436_437, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg435_b
	fill_sequence("seg435_c", &sequences[156], seg436_437, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg435_c
	fill_sequence("seg436_437", &sequences[157], seg440, mr_woe, police, NULL, seg438, seg440, NULL, 118458, 123000, 120625); // seg436_437
	fill_sequence("seg438", &sequences[158], seg439_a, leave_her, convince_her, NULL, seg439_a, seg439_b, NULL, 15833, 19875, 19500); // seg438
	fill_sequence("seg439_a", &sequences[159], seg447, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg439_a
	fill_sequence("seg439_b", &sequences[160], seg439_a, leave_her, take_her, NULL, seg439_a, seg439_c, NULL, 6833, 10083, 9792); // seg439_b
	fill_sequence("seg439_c", &sequences[161], seg447, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg439_c
	fill_sequence("seg440", &sequences[162], seg441, unsure, yes, NULL, seg442_1, seg441, NULL, 14542, 18583, 17583); // seg440
	fill_sequence("seg441", &sequences[163], seg445_1, why_not, im_going, NULL, seg442, seg445_1, NULL, 7500, 11542, 10375); // seg441
	fill_sequence("seg442", &sequences[164], seg443, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg442
	fill_sequence("seg443", &sequences[165], seg445_1, unsure, disagree, NULL, seg444, seg445_1, NULL, 8875, 12917, 10125); // seg443
	fill_sequence("seg444", &sequences[166], seg445, woe, police, NULL, seg446, seg445, NULL, 14042, 19083, 19083); // seg444
	fill_sequence("seg445", &sequences[167], seg554, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg445 (END OF EPISODE -> 05B)
	fill_sequence("seg445_1", &sequences[168], seg445, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg445_1
	fill_sequence("seg446", &sequences[169], seg447, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg446
	fill_sequence("seg447", &sequences[170], seg501_507, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg447 (END OF EPISODE -> 05A)
	fill_sequence("seg442_1", &sequences[171], seg443, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg442_1
	// EPISODE 5A
	fill_sequence("seg501_507", &sequences[172], seg508_1, fortune_cookie, follow_him, NULL, seg508_1, seg509_511, NULL, 81083, 85458, 83333); // seg501_507
	fill_sequence("seg508_1", &sequences[173], seg508_2, refuse, take_one, NULL, seg508_2, seg508_3, NULL, 17958, 21000, 20375); // seg508_1
	fill_sequence("seg508_2", &sequences[174], seg517, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg508_2
	fill_sequence("seg508_3", &sequences[175], seg517, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg508_3
	fill_sequence("seg509_511", &sequences[176], seg516, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg509_511
	fill_sequence("seg516", &sequences[177], seg522, believe, disbelieve, NULL, seg522, seg519, NULL, 108083, 112625, 110833); // seg516
	fill_sequence("seg517", &sequences[178], seg516, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg517
	fill_sequence("seg519", &sequences[179], seg522, accept, object, NULL, seg522, seg520, NULL, 20917, 25500, 20917); // seg519
	fill_sequence("seg520", &sequences[180], eval_cookie, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg520
	fill_sequence("seg522", &sequences[181], eval_cookie, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg522
	fill_sequence("seg524_a", &sequences[182], seg525, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg524_a
	fill_sequence("seg524_b", &sequences[183], seg525, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg524_b
	fill_sequence("seg524_c", &sequences[184], seg525, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg524_c
	fill_sequence("seg525", &sequences[185], seg529_a, better_plan, okay, NULL, seg526, seg529_a, NULL, 23667, 28208, 26667); // seg525
	fill_sequence("seg526", &sequences[186], seg527, go_to_police, follow_her, NULL, seg527, seg529_b, NULL, 52375, 56917, 56417); // seg526
	fill_sequence("seg527", &sequences[187], seg528_b, go_to_police, follow_her, NULL, seg528_b, seg528_a, NULL, 10208, 14750, 14750); // seg527
	fill_sequence("seg528_a", &sequences[188], seg530, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg528_a
	fill_sequence("seg528_b", &sequences[189], seg551, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg528_b (END OF EPISODE -> 05B)
	fill_sequence("seg529_a", &sequences[190], seg530, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg529_a
	fill_sequence("seg529_b", &sequences[191], seg530, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg529_b
	fill_sequence("seg530", &sequences[192], seg601_602_603, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg530 (END OF EPISODE -> 06A)
	// EPISODE 5B
	fill_sequence("seg551", &sequences[193], seg554, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg551
	fill_sequence("seg554", &sequences[194], eval_gone_to_woe, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg554
	fill_sequence("seg561", &sequences[195], seg562_b, dont_mention_may, mention_may, NULL, seg562_a, seg562_b, NULL, 42958, 47333, 46083); // seg561
	fill_sequence("seg555", &sequences[196], eval_sabotage2, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg555
	fill_sequence("seg556_a", &sequences[197], seg557, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg556_a
	fill_sequence("seg556_b", &sequences[198], seg557, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg556_b
	fill_sequence("seg557", &sequences[199], seg558_a, keep_quiet, mention_may, NULL, seg558_a, seg558_b, NULL, 20042, 24083, 21500); // seg557
	fill_sequence("seg558_a", &sequences[200], seg560, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg558_a
	fill_sequence("seg558_b", &sequences[201], seg560, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg558_b
	fill_sequence("seg560", &sequences[202], seg565, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg560
	fill_sequence("seg562_a", &sequences[203], seg563, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg562_a
	fill_sequence("seg562_b", &sequences[204], seg563, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg562_b
	fill_sequence("seg563", &sequences[205], seg564_a, yes, no, NULL, seg564_a, seg564_b, NULL, 27083, 30792, 27708); // seg563
	fill_sequence("seg564_a", &sequences[206], seg565, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg564_A
	fill_sequence("seg564_b", &sequences[207], seg565, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg564_b
	fill_sequence("seg565", &sequences[208], eval_gone_to_woe2, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg565
	fill_sequence("seg568_b", &sequences[209], seg570_571, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg568_b
	fill_sequence("seg568_a", &sequences[210], seg570_571, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg568_a
	fill_sequence("seg570_571", &sequences[211], seg651_1, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg570_571 (END OF EPISODE -> 06B)
	// EPISODE 6A
	fill_sequence("seg601_602_603", &sequences[214], eval_blank_book, kiss, withdraw, NULL, eval_may_likes_matt, eval_blank_book, NULL, 99333, 102917, 102917); // seg601_602_603
	fill_sequence("seg604_c", &sequences[215], seg605_b, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg604_c
	fill_sequence("seg604_d", &sequences[216], seg605_b, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg604_d
	fill_sequence("seg605_b", &sequences[217], seg606, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg605_b
	fill_sequence("seg606", &sequences[218], seg607, explain, ask, NULL, seg607, seg608, NULL, 44250, 48083, 45792); // seg606
	fill_sequence("seg607", &sequences[219], seg610, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg607
	fill_sequence("seg608", &sequences[220], eval_may_kiss, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg608
	fill_sequence("seg610", &sequences[221], seg614_b, go_downstairs, open_window, NULL, seg618, seg614_a, NULL, 17292, 21833, 17292); // seg610
	fill_sequence("seg614_a", &sequences[222], seg615, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg614_a
	fill_sequence("seg614_b", &sequences[223], seg615, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg614_b
	fill_sequence("seg618", &sequences[224], seg619, _continue, go_back, NULL, seg620_621_622, seg619, NULL, 4625, 8000, 6750); // seg618
	fill_sequence("seg615", &sequences[225], seg616_622, upstairs, break_it, NULL, seg617, seg616_622, NULL, 250, 3792, 2792); // seg615
	fill_sequence("seg619", &sequences[226], seg624, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg619
	fill_sequence("seg620_621_622", &sequences[227], seg623_a, trust, dont_trust, NULL, seg623_a, seg623_b, NULL, 25500, 29292, 29292); // seg620_621_622
	fill_sequence("seg616_622", &sequences[228], seg623_b, trust, dont_trust, NULL, seg623_a, seg623_b, NULL, 34500, 38250, 38250); // seg616_622
	fill_sequence("seg617", &sequences[229], seg624, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg617
	fill_sequence("seg623_a", &sequences[230], eval_ep7_start, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg623_a (END OF EPISODE -> 07)
	fill_sequence("seg623_b", &sequences[231], seg651_1, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg623_b (END OF EPISODE -> 06B)
	fill_sequence("seg624", &sequences[232], seg651_1, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg624 (END OF EPISODE -> 06B)
	fill_sequence("seg604_a", &sequences[233], seg606, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg604_a
	fill_sequence("seg604_b", &sequences[234], seg605_b, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg604_b
	fill_sequence("seg609_a", &sequences[235], seg610, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg609_a
	fill_sequence("seg609_b", &sequences[236], seg610, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg609_b
	// EPISODE 6B
	fill_sequence("seg651_1", &sequences[237], eval_report_police, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg651_1
	fill_sequence("seg651_2b", &sequences[238], seg651_3, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg651_2b
	fill_sequence("seg651_2a", &sequences[239], seg651_3, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg651_2a
	fill_sequence("seg651_3", &sequences[240], seg652_b, yes, no, NULL, seg652_a, seg652_b, NULL, 25750, 30292, 26458); // seg651_3
	fill_sequence("seg652_a", &sequences[241], seg653, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg652_a
	fill_sequence("seg652_b", &sequences[242], seg653, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg652_b
	fill_sequence("seg653", &sequences[243], seg654, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg653
	fill_sequence("seg654", &sequences[244], seg655_c, long_one, short_one, NULL, seg655_b, seg655_a, NULL, 542, 5542, 542); // seg654
	fill_sequence("seg655_a", &sequences[245], seg656, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg655_a
	fill_sequence("seg655_b", &sequences[246], seg656, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg655_b
	fill_sequence("seg655_c", &sequences[247], seg656, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg655_c
	fill_sequence("seg656", &sequences[248], seg657, protect_her, save_yourself, NULL, seg657, seg666_a, NULL, 13375, 17917, 14333); // seg656
	fill_sequence("seg666_a", &sequences[249], seg673, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg666_a
	fill_sequence("seg657", &sequences[250], eval_may_likes_matt2, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg657
	fill_sequence("seg660", &sequences[251], seg661, give_in, protect_her, NULL, seg666_a, seg661, NULL, 18708, 22917, 21000); // seg660
	fill_sequence("seg667_669_670_a", &sequences[252], eval_spit_in_the_face, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg667_669_670_a
	fill_sequence("seg667_669_670_b", &sequences[253], eval_spit_in_the_face, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg667_669_670_b
	fill_sequence("seg673", &sequences[254], seg674, say_nothing, object, NULL, seg674, seg675, NULL, 28917, 33125, 33125); // seg673
	fill_sequence("seg671_a", &sequences[255], seg672, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg671_a
	fill_sequence("seg671_b", &sequences[256], seg672, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg671_b
	fill_sequence("seg672", &sequences[257], eval_ep7_start, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg672 (END OF EPISODE -> 07)
	fill_sequence("seg661", &sequences[258], eval_may_likes_matt3, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg661
	fill_sequence("seg674", &sequences[259], eval_ep7_start, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg674 (END OF EPISODE -> 07)
	fill_sequence("seg675", &sequences[260], seg672, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg675
	fill_sequence("seg662", &sequences[261], seg663, give_in, keep_protecting, NULL, seg666_b, seg663, NULL, 2208, 5875, 2208); // seg662
	fill_sequence("seg666_b", &sequences[262], seg673, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg666_b
	fill_sequence("seg663", &sequences[263], eval_may_likes_matt4, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg663
	fill_sequence("seg664", &sequences[264], seg665, give_in, keep_protecting, NULL, seg666_c, seg665, NULL, 27583, 31792, 30583); // seg664
	fill_sequence("seg665", &sequences[265], eval_knife_long, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg665
	fill_sequence("seg666_c", &sequences[266], seg673, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg666_c
	fill_sequence("seg668_669_670_a", &sequences[267], eval_spit_in_the_face, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg668_669_670_a
	fill_sequence("seg668_669_670_b", &sequences[268], eval_spit_in_the_face, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg668_669_670_b
	// EPISODE 7
	fill_sequence("seg732", &sequences[269], seg734, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg732
	fill_sequence("seg701", &sequences[270], seg707, trust_her, no_way, NULL, seg707, seg702, NULL, 84625, 89083, 84625); // seg701
	fill_sequence("seg702", &sequences[271], seg707, conditions, theres_nothing, NULL, seg707, seg703, NULL, 25375, 29792, 28208); // seg702
	fill_sequence("seg707", &sequences[272], seg708, believe, dont_believe, NULL, seg716_723, seg708, NULL, 66667, 70167, 69500); // seg707
	fill_sequence("seg703", &sequences[273], seg707, reconsider, keep_walking, NULL, seg707, seg704, NULL, 22875, 27833, 27125); // seg703
	fill_sequence("seg704", &sequences[274], seg733, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg704
	fill_sequence("seg708", &sequences[275], seg709, let_it_go, push_her, NULL, seg715, seg709, NULL, 6417, 9917, 7250); // seg708
	fill_sequence("seg709", &sequences[276], seg710, let_it_go, push_her, NULL, seg712, seg710, NULL, 24708, 28667, 26083); // seg709
	fill_sequence("seg710", &sequences[277], seg711, comfort_her, walk_away, NULL, seg712, seg711, NULL, 3833, 8292, 6375); // seg710
	fill_sequence("seg711", &sequences[278], seg733, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg711
	fill_sequence("seg712", &sequences[279], seg713_c, kiss_her, dont, NULL, eval_may_kissed_matt, seg713_c, NULL, 22125, 26042, 26042); // seg712
	fill_sequence("seg713_a", &sequences[280], seg714_723, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg713_a
	fill_sequence("seg713_b", &sequences[281], seg714_723, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg713_b
	fill_sequence("seg713_c", &sequences[282], seg714_723, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg713_c
	fill_sequence("seg714_723", &sequences[283], seg724, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg714_723
	fill_sequence("seg724", &sequences[284], seg761, keep_calm, fight, NULL, seg760, seg761, NULL, 71917, 76375, 74208); // seg724
	fill_sequence("seg760", &sequences[285], seg761, keep_calm, react, NULL, seg762, seg761, NULL, 3250, 7125, 6917); // seg760
	fill_sequence("seg761", &sequences[286], seg765_756_757, no, fight, NULL, seg763, seg765_756_757, NULL, 2792, 7250, 7250); // seg761
	fill_sequence("seg762", &sequences[287], seg764, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg762
	fill_sequence("seg763", &sequences[288], seg764, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg763
	fill_sequence("seg764", &sequences[289], seg725_k, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg764
	fill_sequence("seg725_k", &sequences[290], seg727, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg725_k
	fill_sequence("seg727", &sequences[291], seg901_1_901_2, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg727 (END OF EPISODE -> 09A)
	fill_sequence("seg734", &sequences[292], eval_left_may_crying, keep_calm, fight, NULL, seg737, eval_left_may_crying, NULL, 13250, 17208, 16208); // seg734
	fill_sequence("seg738", &sequences[293], seg739_1, no, fight, NULL, seg740, seg739_1, NULL, 2750, 7250, 7250); // seg738
	fill_sequence("seg739_2", &sequences[294], seg739_a, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg739_2
	fill_sequence("seg739_1", &sequences[295], eval_cross_exam, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg739_1
	fill_sequence("seg739_a", &sequences[296], seg747_2_749_750, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg739_a
	fill_sequence("seg739_b", &sequences[297], NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg739_b (END OF EPISODE -> 11)
	fill_sequence("seg733", &sequences[298], seg734, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg733
	fill_sequence("seg715", &sequences[299], seg716_723, will, wont, NULL, seg716_723, eval_turned_away, NULL, 8917, 13417, 10417); // seg715
	fill_sequence("seg717_720", &sequences[300], seg733, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg717_720
	fill_sequence("seg717_718", &sequences[301], seg721_723, turn_back, walk_away, NULL, seg721_723, seg719_720, NULL, 20500, 24500, 21792); // seg717_718
	fill_sequence("seg719_720", &sequences[302], seg733, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg719_720
	fill_sequence("seg716_723", &sequences[303], seg724, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg716_723
	fill_sequence("seg721_723", &sequences[304], seg724, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg721_723
	fill_sequence("seg737", &sequences[305], seg738, keep_calm, react, NULL, seg741, seg738, NULL, 2917, 6917, 6333); // seg737
	fill_sequence("seg738", &sequences[306], seg739_1, no, fight, NULL, seg740, seg739_1, NULL, 2750, 7250, 7250); // seg738
	fill_sequence("seg740", &sequences[307], seg742, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg740
	fill_sequence("seg741", &sequences[308], seg742, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg741
	fill_sequence("seg742", &sequences[309], seg743_k, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg742
	fill_sequence("seg743_k", &sequences[310], seg743_1, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg743_k
	fill_sequence("seg743_1", &sequences[311], seg745, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg743_1
	fill_sequence("seg745", &sequences[312], seg770_2, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg745
	fill_sequence("seg747_2_749_750", &sequences[313], seg770, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg747_2_749_750
	fill_sequence("seg765_756_757", &sequences[314], seg770, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg765_756_757
	fill_sequence("seg770", &sequences[315], eval_ep7_target, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg770 (END OF EPISODE -> 11/09B)
	fill_sequence("seg770_2", &sequences[316], seg951_1_951_2, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg770_2 (END OF EPISODE -> 09B)
	// EPISODE 9A
	fill_sequence("seg901_1_901_2", &sequences[317], eval_knows_about_party, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg901_1_901_2
	fill_sequence("seg902_b", &sequences[318], eval_freak, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg902_b
	fill_sequence("seg902_a", &sequences[319], eval_freak, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg902_a
	fill_sequence("seg903_a", &sequences[320], seg905_2, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg903_a
	fill_sequence("seg903_b", &sequences[321], eval_loser, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg903_b
	fill_sequence("seg904_a", &sequences[322], seg905_2, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg904_a
	fill_sequence("seg904_b_905_1", &sequences[323], eval_hero, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg904_b_905_1
	fill_sequence("seg906_a", &sequences[324], seg947_1_913, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg906_a
	fill_sequence("seg906_b", &sequences[325], eval_key_elo, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg906_b
	fill_sequence("seg907_1", &sequences[326], seg948_1, insist, give_up, NULL, seg907_2, seg948_1, NULL, 8875, 13208, 11833); // seg907_1
	fill_sequence("seg946_1", &sequences[327], seg947_1_913, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg946_1
	fill_sequence("seg905_2", &sequences[328], eval_hero, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg905_2
	fill_sequence("seg907_2", &sequences[329], seg908_b, explain, lie, NULL, eval_key_given, seg908_b, NULL, 10750, 14583, 13917); // seg907_2
	fill_sequence("seg908_a_909_913", &sequences[330], seg914, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg908_a_909_913
	fill_sequence("seg908_c", &sequences[331], seg910, beg_her, bribe_her, NULL, seg911_913, seg910, NULL, 13917, 18458, 15667); // seg908_c
	fill_sequence("seg908_b", &sequences[332], seg912_913, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg908_b
	fill_sequence("seg910", &sequences[333], seg912_913, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg910
	fill_sequence("seg912_913", &sequences[334], seg915, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg912_913
	fill_sequence("seg915", &sequences[335], seg916, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg915
	fill_sequence("seg916", &sequences[336], eval_gone_upstairs, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg916
	fill_sequence("seg917_b", &sequences[337], seg918, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg917_b
	fill_sequence("seg917_a", &sequences[338], seg918, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg917_a
	fill_sequence("seg918", &sequences[339], seg928, keep_bluffing, physical_pressure, maybe_prove_it, seg919, seg928, seg927, 31667, 35875, 31667); // seg918
	fill_sequence("seg919", &sequences[340], seg920, elevator, backstage, NULL, seg921, seg920, NULL, 14667, 19167, 18833); // seg919
	fill_sequence("seg920", &sequences[341], seg928, maybe_keep_bluffing, physical_pressure, NULL, seg927, seg928, NULL, 13292, 17333, 17333); // seg920
	fill_sequence("seg914", &sequences[342], seg916, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg914
	fill_sequence("seg911_913", &sequences[343], seg914, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg911_913
	fill_sequence("seg947_1_913", &sequences[344], seg914, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg947_1_913
	fill_sequence("seg948_1", &sequences[345], seg912_913, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg948_1
	fill_sequence("seg921", &sequences[346], seg922, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg921
	fill_sequence("seg922", &sequences[347], eval_mentioned_trojan, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg922
	fill_sequence("seg923", &sequences[348], seg933_2_937_a_938, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg923
	fill_sequence("seg924", &sequences[349], seg933_2_937_a_938, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg924
	fill_sequence("seg927", &sequences[350], seg922, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg927
	fill_sequence("seg928", &sequences[351], seg929, give_up, threaten_him, NULL, seg928_939, seg929, NULL, 12417, 16917, 15917); // seg928
	fill_sequence("seg928_939", &sequences[352], seg939, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg928_939
	fill_sequence("seg929", &sequences[353], seg930, stop, remove_oxygen, NULL, seg929_939, seg930, NULL, 7917, 12417, 12417); // seg929
	fill_sequence("seg930", &sequences[354], seg931_933_934_a_935, stop, strangle_him, NULL, seg930_939, seg931_933_934_a_935, NULL, 12792, 16292, 16292); // seg930
	fill_sequence("seg930_939", &sequences[355], seg939, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg930_939
	fill_sequence("seg931_933_934_a_935", &sequences[356], seg936, hainsworths, parrs, NULL, seg937_a_938, seg936, NULL, 92083, 97083, 96500); // seg931_933_934_a_935
	fill_sequence("seg929_939", &sequences[357], seg939, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg929_939
	fill_sequence("seg933_2_937_a_938", &sequences[358], seg945, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg933_2_937_a_938
	fill_sequence("seg936", &sequences[359], seg937_b_938, hainsworths, parrs, NULL, seg937_a_938, seg937_b_938, NULL, 24167, 28667, 26167); // seg936
	fill_sequence("seg937_a_938", &sequences[360], seg945, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg937_a_938
	fill_sequence("seg937_b_938", &sequences[361], seg945, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg937_b_938
	fill_sequence("seg939", &sequences[362], seg933_2_937_a_938, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg939
	fill_sequence("seg945", &sequences[363], eval_payback_time, maybe_hainsworths, parr, NULL, /* ep10 */ NULL, /* ep11 */ NULL, NULL, 64292, 70250, 70250); // seg945 (END OF EPISODE -> 11/10)
	// EPISODE 9B
	fill_sequence("seg951_1_951_2", &sequences[364], eval_knows_about_party2, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg951_1_951_2
	fill_sequence("seg952_b", &sequences[365], eval_freak2, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg952_b
	fill_sequence("seg952_a", &sequences[366], eval_freak2, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg952_a
	fill_sequence("seg953_a", &sequences[367], seg955, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg953_a
	fill_sequence("seg953_b", &sequences[368], eval_loser2, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg953_b
	fill_sequence("seg954_a", &sequences[369], seg955, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg954_a
	fill_sequence("seg954_b", &sequences[370], seg955, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg954_b
	fill_sequence("seg955", &sequences[371], eval_hero2, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg955
	fill_sequence("seg956_a_947_2", &sequences[372], seg963, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg956_a_947_2
	fill_sequence("seg956_b", &sequences[373], eval_freak3, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg956_b
	fill_sequence("seg957_1", &sequences[374], seg948_2, insist, give_up, NULL, seg957_2, seg948_2, NULL, 4542, 8667, 7417); // seg957_1
	fill_sequence("seg946_2_947_2", &sequences[375], seg963, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg946_2_947_2
	fill_sequence("seg948_2", &sequences[376], seg962, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg948_2
	fill_sequence("seg958_a_959", &sequences[377], seg963, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg958_a_959
	fill_sequence("seg958_c", &sequences[378], seg960, beg_her, bribe_her, NULL, seg961, seg960, NULL, 14000, 18500, 16250); // seg958_c
	fill_sequence("seg958_b", &sequences[379], seg962, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg958_b
	fill_sequence("seg957_2", &sequences[380], seg958_b, explain, lie, NULL, eval_key_given2, seg958_b, NULL, 10750, 14583, 13542); // seg957_2
	fill_sequence("seg960", &sequences[381], seg962, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg960
	fill_sequence("seg961", &sequences[382], seg963, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg961
	fill_sequence("seg962", &sequences[383], seg964, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg962
	fill_sequence("seg963", &sequences[384], seg965, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg963
	fill_sequence("seg964", &sequences[385], seg965, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg964
	fill_sequence("seg965", &sequences[386], eval_gone_upstairs2, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg965
	fill_sequence("seg966_b", &sequences[387], seg967, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg966_b
	fill_sequence("seg966_a", &sequences[388], seg967, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg966_a
	fill_sequence("seg967", &sequences[389], seg968, keep_bluffing, physical_pressure, maybe_prove_it, seg968, seg975, seg974_1, 34208, 38708, 34208); // seg967
	fill_sequence("seg968", &sequences[390], seg969_b, elevator, backstage, NULL, seg969_a, seg969_b, NULL, 13792, 18375, 13792); // seg968
	fill_sequence("seg969_a", &sequences[391], seg970, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg969_a
	fill_sequence("seg969_b", &sequences[392], seg975, maybe_keep_bluffing, physical_pressure, NULL, seg974_1, seg975, NULL, 8042, 14583, 14583); // seg969_b
	fill_sequence("seg970", &sequences[393], eval_passed_by_seg975, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg970
	fill_sequence("seg970_2", &sequences[394], eval_know_trojan, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg970_2
	fill_sequence("seg970_1", &sequences[395], eval_know_trojan, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg970_1
	fill_sequence("seg971_b", &sequences[396], seg977_979, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg971_b
	fill_sequence("seg971_a", &sequences[397], seg977_979, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg971_a
	fill_sequence("seg974_1", &sequences[398], seg974, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg974_1
	fill_sequence("seg974", &sequences[399], seg970, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg974
	fill_sequence("seg975", &sequences[400], seg976, maybe_prove_it, remove_oxygen, NULL, seg974_2, seg976, NULL, 17125, 21667, 21250); // seg975
	fill_sequence("seg976", &sequences[401], eval_know_trojan2, stop, strangle_him, NULL, seg972, eval_know_trojan2, NULL, 11000, 15292, 15167); // seg976
	fill_sequence("seg973_b", &sequences[402], seg977_978, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg973_b
	fill_sequence("seg973_a", &sequences[403], seg977_978, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg973_a
	fill_sequence("seg972", &sequences[404], eval_know_trojan, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg972
	fill_sequence("seg977_978", &sequences[405], seg988_984_2, auction_house, parrs_house, NULL, eval_thumb_pain, seg988_984_2, NULL, 33542, 39042, 37792); // seg977_978
	fill_sequence("seg990_991_992", &sequences[406], eval_cross_exam3, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg990_991_992 (END OF EPISODE -> 10)
	fill_sequence("seg990_992", &sequences[407], eval_cross_exam3, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg990_992 (END OF EPISODE -> 10)
	fill_sequence("seg994", &sequences[408], eval_payback_time2, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg994 (END OF EPISODE -> 11/10)
	fill_sequence("seg988_984_2", &sequences[409], eval_cross_exam2, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg988_984_2 (END OF EPISODE -> 11)
	fill_sequence("seg974_2", &sequences[410], seg974, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg974_2
	fill_sequence("seg977_979", &sequences[411], eval_thumb_pain, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0); // seg977_979
	// EPISODE 10
	// EPISODE 11
	
	fill_events();
}

int current_lang = -1;
int available_lang[] = {
	LANG_EN, // 0
	LANG_FR, // 1
	LANG_ES, // 2
	LANG_DE, // 3
	LANG_IT, // 4
	LANG_PT_BR, // 5
	LANG_RU, // 6
	LANG_DA, // 7
	LANG_TR, // 8
	LANG_UK, // 9
	LANG_HE, // 10
	LANG_HU, // 11
	// LANG_CH_S, // 12
	// LANG_CH_T, // 13
	// LANG_KO, // 14
	// LANG_JA, // 15
	// LANG_AR, // 16
};

void load_localization_files(int lang) {
	if (sub_handle != NULL) {
		unzClose(sub_handle);
	}
	
	config.language = lang;
	FILE *f;
	switch (lang) {
	case LANG_HU:
		debug_log("Language: Hungarian\n");
		current_lang = 11;
		sub_handle = unzOpen("ux0:data/Late Shift/Subtitles/hu.zip");
		f = fopen("app0:data/lang/hu.str", "r");
		break;
	case LANG_HE:
		debug_log("Language: Hebrew\n");
		current_lang = 10;
		sub_handle = unzOpen("ux0:data/Late Shift/Subtitles/he.zip");
		f = fopen("app0:data/lang/he.str", "r");
		break;
	case LANG_UK:
		debug_log("Language: Ukrainian\n");
		current_lang = 9;
		sub_handle = unzOpen("ux0:data/Late Shift/Subtitles/uk.zip");
		f = fopen("app0:data/lang/uk.str", "r");
		break;
	/*case LANG_KO:
		debug_log("Language: Korean\n");
		current_lang = 14;
		sub_handle = unzOpen("ux0:data/Late Shift/Subtitles/ko.zip");
		f = fopen("app0:data/lang/ko.str", "r");
		break;*/
	case LANG_TR:
		debug_log("Language: Turkish\n");
		current_lang = 8;
		sub_handle = unzOpen("ux0:data/Late Shift/Subtitles/tr.zip");
		f = fopen("app0:data/lang/tr.str", "r");
		break;
	case LANG_DA:
		debug_log("Language: Danish\n");
		current_lang = 7;
		sub_handle = unzOpen("ux0:data/Late Shift/Subtitles/da.zip");
		f = fopen("app0:data/lang/da.str", "r");
		break;
	/*case LANG_JA:
		debug_log("Language: Japanese\n");
		current_lang = 15;
		sub_handle = unzOpen("ux0:data/Late Shift/Subtitles/ja.zip");
		f = fopen("app0:data/lang/ja.str", "r");
		break;*/
	case LANG_FR:
		debug_log("Language: French\n");
		current_lang = 1;
		sub_handle = unzOpen("ux0:data/Late Shift/Subtitles/fr.zip");
		f = fopen("app0:data/lang/fr.str", "r");
		break;
	case LANG_DE:
		debug_log("Language: German\n");
		current_lang = 3;
		sub_handle = unzOpen("ux0:data/Late Shift/Subtitles/de.zip");
		f = fopen("app0:data/lang/de.str", "r");
		break;
	case LANG_IT:
		debug_log("Language: Italian\n");
		current_lang = 4;
		sub_handle = unzOpen("ux0:data/Late Shift/Subtitles/it.zip");
		f = fopen("app0:data/lang/it.str", "r");
		break;
	case LANG_ES:
		debug_log("Language: Spanish\n");
		current_lang = 2;
		sub_handle = unzOpen("ux0:data/Late Shift/Subtitles/es.zip");
		f = fopen("app0:data/lang/es.str", "r");
		break;
	/*case LANG_CH_S:
		debug_log("Language: Simplified Chinese\n");
		current_lang = 12;
		sub_handle = unzOpen("ux0:data/Late Shift/Subtitles/zhs.zip");
		f = fopen("app0:data/lang/zhs.str", "r");
		break;*/
	/*case LANG_CH_T:
		debug_log("Language: Traditional Chinese\n");
		current_lang = 13;
		sub_handle = unzOpen("ux0:data/Late Shift/Subtitles/zht.zip");
		f = fopen("app0:data/lang/zht.str", "r");		
		break;*/
	case LANG_PT_BR:
	case LANG_PT:
		debug_log("Language: Portuguese\n");
		current_lang = 5;
		sub_handle = unzOpen("ux0:data/Late Shift/Subtitles/ptbr.zip");
		f = fopen("app0:data/lang/ptbr.str", "r");
		break;
	case LANG_RU:
		debug_log("Language: Russian\n");
		current_lang = 6;
		sub_handle = unzOpen("ux0:data/Late Shift/Subtitles/ru.zip");
		f = fopen("app0:data/lang/ru.str", "r");
		break;
	default:
		debug_log("Language: English\n");
		current_lang = 0;
		sub_handle = unzOpen("ux0:data/Late Shift/Subtitles/en.zip");
		f = fopen("app0:data/lang/en.str", "r");
		break;
	}
	
	// Loading game strings on memory
	int i = 0;
	while (fgets(game_strings[i], 128, f)) {
		if (game_strings[i][strlen(game_strings[i]) - 1] == '\n')
			game_strings[i][strlen(game_strings[i]) - 1] = 0;
		i++;
	}
	fclose(f);
	
	// Appending IDs to sensitive strings so that dear ImGui won't lose focus when a change of language happens
	sprintf(game_strings[9], "%s###options", game_strings[9]);
}

void menu_setup() {
	// Setting up engine theme for menu
	set_theme_color(colors.btn_hover_bg, 0.0f, 0.0f, 0.0f, 0.0f);
	set_theme_color(colors.btn_bg, 0.0f, 0.0f, 0.0f, 0.0f);
	set_theme_color(colors.bar_bg, 0.62745f, 0.62745f, 0.62745f, 1.0f);
	set_theme_color(colors.bar, 1.0f, 1.0f, 1.0f, 1.0f);
	set_theme_color(colors.text, 1.0f, 1.0f, 1.0f, 1.0f);
	set_theme_color(colors.btn_text, 0.18431f, 0.18431f, 0.18431f, 1.0f);
	set_theme_color(colors.btn_hover_text, 1.0f, 1.0f, 1.0f, 1.0f);
	set_theme_color(colors.popup_bg, 0.0f, 0.0f, 0.0f, 0.0f);
	set_theme_color(colors.shadow_text, 0.0f, 0.0f, 0.0f, 0.0f);
	colors.bar_type = BAR_DEFAULT;
}

void game_pause_menu(int *first_call) {
	static int in_options;
	static int btns_state[8];
	static int lang_changed = 0;
	
	if (*first_call) {
		audio_sound_play(snd_pause);
		*first_call = 0;
		in_options = 0;
		lang_changed = 0;
		memset(btns_state, 0, sizeof(int) * 8);
	}
	
	// Calculating button centering positions
	float x_resume = calc_centered_button_pos(game_strings[22]);
	float x_exitgame = calc_centered_button_pos(game_strings[23]);
	float x_options = calc_centered_button_pos(game_strings[9]);
	float x_back = calc_centered_button_pos(game_strings[3]);
	float x_volume = calc_centered_button_pos(game_strings[14]);
	float x_music_volume = calc_centered_button_pos(game_strings[15]);
	char subtitles_text[256], lang_text[256];
	sprintf(subtitles_text, "%s: %s###sub", game_strings[16], config.subtitles ? game_strings[0] : game_strings[1]);
	float x_subtitles = calc_centered_button_pos(subtitles_text);
	sprintf(lang_text, "%s: %s###lang", game_strings[17], game_strings[18]);
	float x_lang = calc_centered_button_pos(lang_text);
	
	if (!in_options) {
		init_menu(0.9f, 0.0f, 0.0f, 960.0f, 544.0f, "##pause_menu");
		if (draw_main_button(x_resume, 200, game_strings[22], &btns_state[0])) {
			game_state = GAME_RESUMING;
			audio_sound_play(snd_unpause);
			if (lang_changed)
				reload_subtitles(cur_seq); // Reloading current sequence subtitles
		}
		if (draw_button(x_options, 250, game_strings[9], &btns_state[1])) {
			in_options = 1;
		}
		if (draw_button(x_exitgame, 300, game_strings[10], &btns_state[2])) {
			game_state = GAME_EXITING;
			audio_sound_play(snd_unpause);
		}
		end_menu();
	} else {
		init_menu(0.9f, 0.0f, 0.0f, 960.0f, 544.0f, "##options");
		if (draw_selector(x_lang, 170, lang_text, &btns_state[4], &current_lang, sizeof(available_lang) / sizeof(*available_lang))) {
			load_localization_files(available_lang[current_lang]);
			lang_changed = 1;
		}
		draw_selector(x_subtitles, 210, subtitles_text, &btns_state[5], &config.subtitles, 2);
		int vol = (int)(config.master_volume * 255.0f);
		draw_fast_selector(x_volume, 245, game_strings[14], &btns_state[9], &vol, 255);
		config.master_volume = (float)vol / 255.0f;
		draw_progressbar(352, 275, 256, 6, config.master_volume, "##barvol");
		int mus_vol = (int)(config.music_volume * 255.0f);
		draw_fast_selector(x_music_volume, 285, game_strings[15], &btns_state[10], &mus_vol, 255);
		config.music_volume = (float)mus_vol / 255.0f;
		draw_progressbar(352, 315, 256, 6, config.music_volume, "##barmusvol");
		audio_set_global_volume(config.master_volume);
		if (draw_button(x_back, 325, game_strings[3], &btns_state[6])) {
			in_options = 0;
			FILE *f = fopen(CONFIG_FILE, "wb");
			fwrite(&config, 1, sizeof(engine), f);
			fclose(f);
			video_set_volume(config.master_volume);
			audio_sample_reset_volume_all();
		}
		end_menu();
	}
}

void game_main_menu() {
	// Loading animated background and audio background
	load_animated_bg("000_MenuBackground", 1);
	int bg_audio_handle;
	void *bg_audio = audio_track_play("EP01 Car Park Melody", 1, 1.0f, &bg_audio_handle);
	
	SceIoStat st;
	int has_save = sceIoGetstat(SAVE_FILE, &st) ? 0 : 1;
	int btns_state[10];
	int in_options = 0;
	int request_new_game = 0;
	
	char version_text[256];
	sprintf(version_text, "OpenFMV v.%s (LS v.%s)", ENGINE_VER, GAME_VER);
	sequence *out = NULL;
	while (!out) {
		if (draw_video_frame()) {
			init_ui_frame();
			
			// Calculating button centering positions
			float x_resume = calc_centered_button_pos(game_strings[6]);
			float x_newgame = calc_centered_button_pos(game_strings[4]);
			float x_options = calc_centered_button_pos(game_strings[9]);
			float x_exitgame = calc_centered_button_pos(game_strings[10]);
			float x_back = calc_centered_button_pos(game_strings[3]);
			float x_volume = calc_centered_button_pos(game_strings[14]);
			float x_music_volume = calc_centered_button_pos(game_strings[15]);
			char subtitles_text[256], lang_text[256];
			sprintf(subtitles_text, "%s: %s###sub", game_strings[16], config.subtitles ? game_strings[0] : game_strings[1]);
			float x_subtitles = calc_centered_button_pos(subtitles_text);
			sprintf(lang_text, "%s: %s###lang", game_strings[17], game_strings[18]);
			float x_lang = calc_centered_button_pos(lang_text);
			float x_newgame_warn = calc_centered_button_pos(game_strings[5]);
			
			init_menu(0.0f, 0.0f, 0.0f, 960.0f, 600.0f, "##main_menu");
			if (!in_options) {
				if (has_save) {
					if (draw_main_button(x_resume, 200, game_strings[6], &btns_state[0])) {
						// Loading progress save
						char hash[64] = {0};
						FILE *f = fopen(SAVE_FILE, "r");
						if (f) {
							fread(hash, 1, 32, f);
							fread(&game_vars, 1, sizeof(gamestate), f);
							fclose(f);
						}
					
						// Resuming save
						for (int i = 0; i < NUM_SEQUENCES; i++) {
							if (!strcmp(hash, sequences[i].hash)) {
								debug_log("Booting sequence #%d\n", i);
								out = &sequences[i];
								break;
							}	
						}
					}
					if (draw_button(x_newgame, 250, game_strings[4], &btns_state[1])) {
						request_new_game = 1;
					}
				} else {
					if (draw_main_button(x_newgame, 250, game_strings[4], &btns_state[1])) {
						request_new_game = 1;
					}
				}
				if (draw_button(x_options, 300, game_strings[9], &btns_state[2])) {
					in_options = 1;
				}
				if (draw_button(x_exitgame, 350, game_strings[10], &btns_state[3])) {
					sceKernelExitProcess(0);
				}
			}
			draw_text(5, 515, version_text, colors.text);
			end_menu();
			
			if (in_options) {
					init_menu(0.8f, 0.0f, 0.0f, 960.0f, 544.0f, "##options");
					if (draw_selector(x_lang, 170, lang_text, &btns_state[4], &current_lang, sizeof(available_lang) / sizeof(*available_lang))) {
						load_localization_files(available_lang[current_lang]);
					}
					draw_selector(x_subtitles, 210, subtitles_text, &btns_state[5], &config.subtitles, 2);
					int vol = (int)(config.master_volume * 255.0f);
					draw_fast_selector(x_volume, 245, game_strings[14], &btns_state[9], &vol, 255);
					config.master_volume = (float)vol / 255.0f;
					draw_progressbar(352, 275, 256, 6, config.master_volume, "##barvol");
					int mus_vol = (int)(config.music_volume * 255.0f);
					draw_fast_selector(x_music_volume, 285, game_strings[15], &btns_state[10], &mus_vol, 255);
					config.music_volume = (float)mus_vol / 255.0f;
					draw_progressbar(352, 315, 256, 6, config.music_volume, "##barmusvol");
					audio_set_global_volume(config.master_volume);
					audio_track_set_volume(bg_audio_handle, 1.0f);
					if (draw_button(x_back, 325, game_strings[3], &btns_state[6])) {
						in_options = 0;
						FILE *f = fopen(CONFIG_FILE, "wb");
						fwrite(&config, 1, sizeof(engine), f);
						fclose(f);
					}
					end_menu();
			} else if (request_new_game) {
				if (has_save) {
					float w = 960.0f - x_newgame_warn * 2;
					init_menu(1.0f, x_newgame_warn, 200.0f, w, 100.0f, "##warning");
					draw_centered_text(5.0f, game_strings[5]);
					if (draw_main_button(w / 4, 60.0f, game_strings[2], &btns_state[7])) {
						// Starting new game
						debug_log("Booting first sequence\n");
						trigger_save = 1;
						out = &sequences[0];
						memset(&game_vars, 0, sizeof(gamestate));
					}
					if (draw_button(w - w / 4 - (960.0f - 2 * x_back), 60.0f, game_strings[3], &btns_state[8])) {
						request_new_game = 0;
					}
					end_menu();
				} else {
					// Starting new game
					debug_log("Booting first sequence\n");
					trigger_save = 1;
					out = &sequences[0];
					memset(&game_vars, 0, sizeof(gamestate));
				}
			}
			
			end_ui_frame();
			vglSwapBuffers(GL_FALSE);
		}
	}
	
	audio_track_stop(bg_audio);
	set_subs_window(0, 474, 960, 70);
	start_first_sequence(out);
}

void game_setup() {
	// Setting up engine theme for game
	set_theme_color(colors.btn_hover_bg, 1.0f, 1.0f, 1.0f, 1.0f);
	set_theme_color(colors.btn_bg, 0.0f, 0.0f, 0.0f, 0.3f);
	set_theme_color(colors.bar_bg, 0.62745f, 0.62745f, 0.62745f, 1.0f);
	set_theme_color(colors.bar, 1.0f, 1.0f, 1.0f, 1.0f);
	set_theme_color(colors.text, 1.0f, 1.0f, 1.0f, 1.0f);
	set_theme_color(colors.btn_text, 1.0f, 1.0f, 1.0f, 1.0f);
	set_theme_color(colors.btn_hover_text, 0.0f, 0.0f, 0.0f, 1.0f);
	set_theme_color(colors.popup_bg, 0.0f, 0.0f, 0.0f, 0.0f);
	set_theme_color(colors.shadow_text, 0.0f, 0.0f, 0.0f, 0.0f);
	colors.choice1[1] = colors.choice2[1] = colors.choice3[1] = 400.0f;
	colors.choice_bar[0] = 239.0f;
	colors.choice_bar[1] = 450.0f;
	colors.choice_bar[2] = 480.0f;
	colors.choice_bar[3] = 6.0f;
	colors.choices_type = CHOICES_CENTER_POS;
	colors.bar_type = BAR_CENTER_FILL;
}

void game_prepare() {
	for (int i = 0; i < NUM_AUDIO_SOURCES; i++) {
		mus[i] = NULL;
	}
}

#endif
