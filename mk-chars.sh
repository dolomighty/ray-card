#!/bin/bash

ASC=33
HGT=16

echo "static unsigned char charset[][$HGT] = {"

od -tu1 -Ax -j$((0x163+$HGT*($ASC-16))) -w$HGT F1.COM |\
awk -v ASC=$ASC -v HGT=$HGT '
function BIN(V){
  STR=""
  for( MASK=0x80 ; MASK ; MASK=int(MASK/2) ){
    STR=STR (and(V,MASK)?"#":".")
  }
  return STR
}
ASC>=127 { exit }
{
  print "// " ASC
  print SEP1 "{"
  SEP2=" "
  for( I=2 ; I<HGT+2 ; I++ ){
    printf("%c0x%02x // %s\n",SEP2,$I,BIN($I))
    SEP2=","
  }
  print "}"
  SEP1=","
  ASC++
}'

echo "};"

