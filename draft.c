void	calc_run(int key_code, t_main *main)
{
	t_calc *c;

	c = c;
	if (key_code == W_KEY)
	{
		c->x_run = fabs(cos(c->pdir)) * c->pdir_stepx * RUN;
		c->y_run = fabs(sin(c->pdir)) * c->pdir_stepy * RUN;
	}
	else if (key_code == S_KEY)
	{
		c->x_run = fabs(cos(c->pdir)) * c->pdir_stepx * -1 * RUN;
		c->y_run = fabs(sin(c->pdir)) * c->pdir_stepy * -1 * RUN;
	}
	else if (key_code == A_KEY)
	{
		c->x_run = fabs(sin(c->pdir)) * c->pdir_stepy * -1 * RUN;
		c->y_run = fabs(cos(c->pdir)) * c->pdir_stepx * RUN;
	}
	else if (key_code == D_KEY)
	{
		c->x_run = fabs(sin(c->pdir)) * c->pdir_stepy * RUN;
		c->y_run = fabs(cos(c->pdir)) * c->pdir_stepx * -1 * RUN;
	}
}