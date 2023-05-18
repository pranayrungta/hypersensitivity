struct Local_dynamics
{
	double  m   = 1     ;
	double	ro1 = 2.0   ;
	double	ro2 = 0.08  ;
	double	alp = 11    ;
	double	gam = 5.215 ;

	double operator()(const double& x)const
	{
		return (
            m*( 1 + x*x + alp*ro1*x*x*x*x )/
	   ( 1 + x*x + ro1*x*x*x*x + ro1*ro2*x*x*x*x*x*x)   - gam*x  );
	}
};
