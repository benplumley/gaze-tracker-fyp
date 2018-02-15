function r = RotA_temp(raxis, angle, ~)
raxis(4,:) = angle;
r = vrrotvec2mat(raxis);
return;