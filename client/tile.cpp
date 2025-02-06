#include "tile.h"

void Tile::set_team_visible(TeamType team, bool is_visible)
{
	switch (team)
	{
	case TeamType::Blue:
		team_visible.BlueVisible = is_visible;
		break;
	case TeamType::Red:
		team_visible.RedVisible = is_visible;
		break;
	case TeamType::Yellow:
		team_visible.YellowVisible = is_visible;
		break;
	case TeamType::Green:
		team_visible.GreenVisible = is_visible;
		break;
	case TeamType::Pink:
		team_visible.PinkVisible = is_visible;
		break;
	case TeamType::Orange:
		team_visible.OrangeVisible = is_visible;
		break;
	default:
		break;
	}
}