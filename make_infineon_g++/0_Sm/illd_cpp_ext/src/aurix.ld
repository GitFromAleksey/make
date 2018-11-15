MEMORY
{
	df0_ucb4 (w!xp): org = 0xAF101000, len = 1K
	periphery (w!xp): org = 0xF0000000, len = 256M
}

SECTIONS
{
    .aurix.ucb4 (NOLOAD): FLAGS(aw)
    {
        *(.aurix.ucb4)
    }>df0_ucb4

    .aurix.gtm 0xF0100000 (NOLOAD): FLAGS(awz)
    {
        *(.aurix.gtm)
    }>periphery

    .aurix.pmu0 0xF8000500 (NOLOAD): FLAGS(aw)
    {
        *(.aurix.pmu0)
    }>periphery
}
