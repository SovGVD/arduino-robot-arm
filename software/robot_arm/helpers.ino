double mapf(double val, double in_min, double in_max, double out_min, double out_max) {
  return (val - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

double dcos (double deg)
{
  return cos(deg*DEGTORAD);
}

double dsin (double deg)
{
  return sin(deg*DEGTORAD);
}
