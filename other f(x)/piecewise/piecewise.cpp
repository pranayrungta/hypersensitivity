struct Local_dynamics
{
	double  xu = 1.0   ;
	double  xl = -1.0  ;
	double  alp = 1.8  ;
	double  bet = 3.0  ;

	double operator()(const double& x)const
	{
		if(x<xl)
			return -alp*x +bet*xl;
		else if(x<=xu)
			return -alp*x +bet*x;
		else
			return -alp*x +bet*xu;
	}
};
