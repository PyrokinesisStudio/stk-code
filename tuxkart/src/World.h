//  $Id: World.h,v 1.16 2004/09/24 18:41:26 matzebraun Exp $
//
//  TuxKart - a fun racing game with go-kart
//  Copyright (C) 2004 Steve Baker <sjbaker1@airmail.net>
//
//  This program is free software; you can redistribute it and/or
//  modify it under the terms of the GNU General Public License
//  as published by the Free Software Foundation; either version 2
//  of the License, or (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the Free Software
//  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

#ifndef HEADER_WORLD_H
#define HEADER_WORLD_H

#include <plib/ssg.h>
#include <vector>
#include "RaceSetup.h"

#define NUM_PROJECTILES  8
#define NUM_EXPLOSIONS   6

class Herring;
class KartDriver;
class Projectile;
class Explosion;
class Track;
class guUDPConnection;

/** This class keeps all the state of a race, scenegraph, time,
    etc. */
class World
{
public:
  ssgRoot      *scene;

  typedef std::vector<KartDriver*> Karts;
private:
  Karts kart;

public:
  typedef std::vector<Projectile*> Projectiles;
  Projectiles projectiles;
  Explosion   *explosion [ NUM_EXPLOSIONS  ] ;
  float clock;

  /** resources, this should be put in a separate class or replaced by a smart
   * resource manager
   */
  ssgEntity* projectile_spark;
  ssgEntity* projectile_missle;
  ssgEntity* projectile_flamemissle;

  RaceSetup raceSetup;

  enum Phase { 
    // The traffic light is shown and all players stay in position
    START_PHASE,
    // The traffic light turned green and all driver, drive around the track
    RACE_PHASE,
    // The player crossed the finishing line and his and the time of
    // the other players is displayed, controll is automatic
    FINISH_PHASE 
  };

  int ready_set_go;

  const Track* track;
private:
  Herring *silver_h ;
  Herring *gold_h   ;
  Herring *red_h    ;
  Herring *green_h  ;

  Phase phase;
public:
  /** debug text that will be overlaid to the screen */
  std::string debugtext[10];
  
  /** Reference to the track inside the scene */
  ssgBranch *trackBranch ;

  World(const RaceSetup& raceSetup);
  virtual ~World();

  void draw();
  void update(float delta);
  void restartRace();
  
  KartDriver* getPlayerKart(int player);
  KartDriver* getKart(int kart); 
  int getNumKarts() const { return kart.size(); }
  
  /** Returns the phase of the game */
  Phase getPhase() const { return phase; }
private:
  void updateLapCounter ( int k );
  void loadTrack();
  void loadPlayers();
  void herring_command(char *s, char *str );
  void checkRaceStatus();
};

extern World* world;

#endif

/* EOF */
