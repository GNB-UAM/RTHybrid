#!/bin/bash
sudo ./RTHybrid -xml xml/test_times_hr.xml
echo "\nhr ended" 
sudo ./RTHybrid -xml xml/test_times_rlk.xml
echo "\nrlk ended" 
sudo ./RTHybrid -xml xml/test_times_gh.xml
echo "\ngh ended"
