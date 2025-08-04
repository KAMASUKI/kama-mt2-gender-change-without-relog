// Search
// bool CHARACTER::ChangeSex()
// sys_log(0, "CHANGE_SEX: %s (%d -> %d)", GetName(), src_race, m_points.job);


// Add above

#ifdef ENABLE_GENDER_CHANGE_WITHOUT_RELOG
	BYTE currentSex = GET_SEX(this);
	LPITEM costumes[2] = { GetWear(WEAR_COSTUME_BODY), GetWear(WEAR_COSTUME_HAIR) };
	for (int i = 0; i < 2; ++i)
	{
		LPITEM costume = costumes[i];
		if (!costume)
			continue;

		if ((currentSex == SEX_MALE && IS_SET(costume->GetAntiFlag(), ITEM_ANTIFLAG_MALE)) ||
			(currentSex == SEX_FEMALE && IS_SET(costume->GetAntiFlag(), ITEM_ANTIFLAG_FEMALE)))
		{
			UnequipItem(costume);
		}
	}

	UpdatePacket();
	SET_BIT(m_bAddChrState, ADD_CHARACTER_STATE_SPAWN);
	m_afAffectFlag.Set(AFF_SPAWN);
	ViewReencode();
	REMOVE_BIT(m_bAddChrState, ADD_CHARACTER_STATE_SPAWN);
	m_afAffectFlag.Reset(AFF_SPAWN);
#endif

// Like this

bool CHARACTER::ChangeSex()
{
	int src_race = GetRaceNum();

	switch (src_race)
	{
		case MAIN_RACE_WARRIOR_M:
			m_points.job = MAIN_RACE_WARRIOR_W;
			break;

		case MAIN_RACE_WARRIOR_W:
			m_points.job = MAIN_RACE_WARRIOR_M;
			break;

		case MAIN_RACE_ASSASSIN_M:
			m_points.job = MAIN_RACE_ASSASSIN_W;
			break;

		case MAIN_RACE_ASSASSIN_W:
			m_points.job = MAIN_RACE_ASSASSIN_M;
			break;

		case MAIN_RACE_SURA_M:
			m_points.job = MAIN_RACE_SURA_W;
			break;

		case MAIN_RACE_SURA_W:
			m_points.job = MAIN_RACE_SURA_M;
			break;

		case MAIN_RACE_SHAMAN_M:
			m_points.job = MAIN_RACE_SHAMAN_W;
			break;

		case MAIN_RACE_SHAMAN_W:
			m_points.job = MAIN_RACE_SHAMAN_M;
			break;
#ifdef ENABLE_WOLFMAN_CHARACTER
		case MAIN_RACE_WOLFMAN_M:
			m_points.job = MAIN_RACE_WOLFMAN_M;
			break;
#endif
		default:
			sys_err("CHANGE_SEX: %s unknown race %d", GetName(), src_race);
			return false;
	}

#ifdef ENABLE_GENDER_CHANGE_WITHOUT_RELOG
	BYTE currentSex = GET_SEX(this);
	LPITEM costumes[2] = { GetWear(WEAR_COSTUME_BODY), GetWear(WEAR_COSTUME_HAIR) };
	for (int i = 0; i < 2; ++i)
	{
		LPITEM costume = costumes[i];
		if (!costume)
			continue;

		if ((currentSex == SEX_MALE && IS_SET(costume->GetAntiFlag(), ITEM_ANTIFLAG_MALE)) ||
			(currentSex == SEX_FEMALE && IS_SET(costume->GetAntiFlag(), ITEM_ANTIFLAG_FEMALE)))
		{
			UnequipItem(costume);
		}
	}

	UpdatePacket();
	SET_BIT(m_bAddChrState, ADD_CHARACTER_STATE_SPAWN);
	m_afAffectFlag.Set(AFF_SPAWN);
	ViewReencode();
	REMOVE_BIT(m_bAddChrState, ADD_CHARACTER_STATE_SPAWN);
	m_afAffectFlag.Reset(AFF_SPAWN);
#endif

	sys_log(0, "CHANGE_SEX: %s (%d -> %d)", GetName(), src_race, m_points.job);
	return true;
}