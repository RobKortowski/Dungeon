/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Map.cpp
 * Author: Robert Kortowski robjudo@wp.pl
 * 
 * Created on March 19, 2017, 7:43 PM
 */

#include "Map.h"
#include "Entity.h"
#include "Chunk.h"
#include "InnerCube.h"
#include "Block.h"
#include "Dirt.h"
#include "Air.h"
#include <algorithm>
#include <vector>

using namespace std;

Map::Map(int gameNum) : gameNum(gameNum) {
    generate(100/*0*/, 100/*0*/, 100, Mode::Flat);
    generateBlockConstInfo();
}

Map::~Map() {
}

void Map::allocateMap(int x, int y, int z) {
    this->x = x - 1;
    this->y = y - 1;
    this->z = z - 1;
    /*chunks = new Chunk**[z];
    for (int i = 0; i < z; ++i) {
        chunks[i] = new Chunk*[x];
        for (int j = 0; j < x; ++j) {
            chunks[i][j] = new Chunk[y];
        }
    }
     */

    chunks = new v3d(x, v2d(y, v1d(z)));


    for (int i = 0; i < x; ++i) {
        for (int j = 0; j < y; ++j) {
            for (int k = 0; k < z; ++k) {
                (*chunks)[i][j][k] = new Chunk();
                (*chunks)[i][j][k]->x = i;
                (*chunks)[i][j][k]->y = j;
                (*chunks)[i][j][k]->z = k;

            }
        }
    }
}

void Map::generate(int x, int y, int z, Mode m) {
    allocateMap(x, y, z);
    switch (m) {
        case Mode::Flat:
            for (int i = 0; i < x; ++i) {
                for (int j = 0; j < y; ++j) {
                    for (int k = 0; k < z; ++k) {
                        (*chunks)[i][j][k]->generated = false;
                        (*chunks)[i][j][k]->loaded = false;
                        if (k > z / 2) {

                            (*chunks)[i][j][k]->type = ChunkType::air;

                        } else if (k == z / 2) {

                            (*chunks)[i][j][k]->ics = new ChunkSeed();
                            (*chunks)[i][j][k]->type = ChunkType::midground;
                            (*chunks)[i][j][k]->ics->groundLevel = 5;
                        } else {
                            (*chunks)[i][j][k]->ics = new ChunkSeed();
                            (*chunks)[i][j][k]->type = ChunkType::underground;
                        }
                    }
                }
            }
            break;
        default:
            break;
    }
}

void Map::calcTurns(double time) {
    for (vector<Entity*>::iterator it = woken.begin(); it != woken.end(); ++it) {
        (*it)->calcTurn();
    }
    for (vector<Player*>::iterator it = players.begin(); it != players.end(); ++it) {
        (*it)->calcTurn();
    }
}

void Map::doTurns() {
    for (vector<Entity*>::iterator it = woken.begin(); it != woken.end(); ++it) {
        (*it)->doTurn();
    }
    for (vector<Player*>::iterator it = players.begin(); it != players.end(); ++it) {
        (*it)->doTurn();
    }
}

void Map::calculateVisible() {
    for (vector<Entity*>::iterator it = woken.begin(); it != woken.end(); ++it) {
        Chunk* c = (*chunks)[(*it)->x][(*it)->y][(*it)->z];
        InnerCube* ic = (*c->cubes)[(int) (*it)->xx / 10][(int) (*it)->yy / 10][(int) (*it)->zz / 10];
        (*it)->clearVisible();
        for (Block* b : (*(ic->visible))) {
            (*it)->addVisible(b);
        }
    }
    //TODO for left chunk to right ... etc 
    for (vector<Player*>::iterator it = players.begin(); it != players.end(); ++it) {
        Player* pp = (*it);
        vector<Block*> tmp;
        int radius = (*it)->getProperty(1);
        int offx = (int) pp->xx;
        int offy = (int) pp->yy;
        int offz = (int) pp->zz;
        //TODO bound also with map bounds
        int minx = (offx - radius >= 0 ? 0 : -1);
        int maxx = (offx + radius < ICS * ICS ? 0 : 1);
        int miny = (offy - radius >= 0 ? 0 : -1);
        int maxy = (offy + radius < ICS * ICS ? 0 : 1);
        int minz = (offz - radius >= 0 ? 0 : -1);
        int maxz = (offz + radius < ICS * ICS ? 0 : 1);
        for (int i = minx; i <= maxx; ++i) {
            for (int j = miny; j <= maxy; ++j) {
                for (int k = minz; k <= maxz; ++k) {
                    Chunk * c = (*chunks)[pp->x + i][pp->y + j][pp->z + k];
                    if (c->type != ChunkType::midground) {
                        continue;
                    }
                    int cubex, cubexx, cubez, cubezz, cubey, cubeyy;
                    if (i < 0) {
                        cubex = ICS - 1 - (offx - radius) / 10;
                        cubexx = ICS - 1;
                    } else if (i > 0) {
                        cubex = 0;
                        cubexx = (radius - (ICS * ICS - 1 - offx)) / 10;
                    } else {
                        cubex = (offx - radius <= 0 ? 0 : (offx - radius) / 10);
                        cubexx = (offx + radius >= ICS * ICS ? ICS - 1 : (offx + radius) / 10);
                    }
                    if (j < 0) {
                        cubey = ICS - 1 - (offy - radius) / 10;
                        cubeyy = ICS - 1;
                    } else if (j > 0) {
                        cubey = 0;
                        cubeyy = (radius - (ICS * ICS - 1 - offy)) / 10;
                    } else {
                        cubey = (offy - radius <= 0 ? 0 : (offy - radius) / 10);
                        cubeyy = (offy + radius >= ICS * ICS ? ICS - 1 : (offy + radius) / 10);
                    }
                    if (k < 0) {
                        cubez = ICS - 1 - (offz - radius) / 10;
                        cubezz = ICS - 1;
                    } else if (k > 0) {
                        cubez = 0;
                        cubezz = (radius - (ICS * ICS - 1 - offz)) / 10;
                    } else {
                        cubez = (offz - radius <= 0 ? 0 : (offz - radius) / 10);
                        cubezz = (offz + radius >= ICS * ICS ? ICS - 1 : (offz + radius) / 10);
                    }
                    for (int r = cubex; r <= cubexx; ++r) {
                        for (int t = cubey; t <= cubeyy; ++t) {
                            for (int u = cubez; u <= cubezz; ++u) {
                                InnerCube * ic = (*c->cubes)[r][t][u];
                                if (ic->type != InnerCubeType::midground) {
                                    continue;
                                }
                                for (Block* b : (*ic->visible)) {
                                    //TODO check if in radius
                                    tmp.push_back(b);
                                }

                            }
                        }
                    }
                }
            }
        }
        //TODO get difference section with players previous set
        pp->clearVisible();
        b1d pingBlocks(tmp.size());
        b1d unpingBlocks(tmp.size());
        std::vector<Block*>::iterator itt;
	
	//sort(pp->visibleBlocks.begin(), pp->visibleBlocks.end(), Map::compareBlocks);
	//sort(tmp.begin(), tmp.end(), Map::compareBlocks);
	
        itt = std::set_difference(tmp.begin(), tmp.end(), pp->visibleBlocks.begin(), pp->visibleBlocks.end(), pingBlocks.begin(), Map::compareBlocks);
        pingBlocks.resize(itt - pingBlocks.begin());
        
	Chunk* c;
        InnerCube* ic;
        for (Block* b : pingBlocks) {
            if (b->parent != ic) {
                ic = b->parent;
                if (ic->parent != c) {
                    c = ic->parent;
                    pp->addToLog(c->to_string());
                }
                pp->addToLog(ic->to_string());
            }
            pp->addToLog(b->to_string());
        }
        pp->visibleBlocks = tmp;
    }
}

bool Map::compareBlocks(const Block* a, const Block* b) {
    if(a==b){
	return false;
    }
    if (a->parent->parent->x != b->parent->parent->x) {
        return a->parent->parent->x < b->parent->parent->x;
    } else if (a->parent->parent->y != b->parent->parent->y) {
        return a->parent->parent->y < b->parent->parent->y;
    } else if (a->parent->parent->z != b->parent->parent->z) {
        return a->parent->parent->z < b->parent->parent->z;
    } else if (a->parent->x != b->parent->x) {
        return a->parent->x < b->parent->x;
    } else if (a->parent->y != b->parent->y) {
        return a->parent->y < b->parent->y;
    } else if (a->parent->z != b->parent->z) {
        return a->parent->z < b->parent->z;
    } else if (a->x != b->x) {
        return a->x < b->x;
    } else if (a->y != b->y) {
        return a->y < b->y;
    } else if (a->z != b->z) {
        return a->z < b->z;
    } else {
        return false;
    }
}

void Map::wakeEntity(Entity* e) {
    woken.push_back(e);
}

void Map::sleepEntity(Entity* e) {
    woken.erase(remove(woken.begin(), woken.end(), e), woken.end());
}

void Map::ascend(Player* p) {
    int minx = (0 < p->x ? p->x - 1 : 0);
    int maxx = (x > p->x ? p->x + 1 : x);
    int miny = (0 < p->y ? p->y - 1 : 0);
    int maxy = (y > p->y ? p->y + 1 : y);
    int minz = (0 < p->z ? p->z - 1 : 0);
    int maxz = (z > p->z ? p->z + 1 : z);
    for (int i = minx; i <= maxx; ++i) {
        for (int j = miny; j <= maxy; ++j) {
            for (int k = minz; k <= maxz; ++k) {
                if ((*chunks)[i][j][k]->loaded) {
                    continue;
                } else if ((*chunks)[i][j][k]->generated) {
                    //TODO load chunk from file 
                } else {
                    fillChunk((*chunks)[i][j][k]);
                }
            }
        }
    }
}

void Map::fillChunk(Chunk*& c) {
    if (c->type == ChunkType::midground) {
        c->generated = true;
        c->loaded = true;
        i3d* cubes = new i3d(ICS, i2d(ICS, i1d(ICS)));
        int gLvl = c->ics->groundLevel;
        for (int i = 0; i < ICS; ++i) {
            for (int j = 0; j < ICS; ++j) {
                for (int k = 0; k < ICS; ++k) {
                    InnerCube* tmp = new InnerCube();
                    tmp->x = i;
                    tmp->y = j;
                    tmp->z = k;
                    tmp->pos = &(Lookup[i][j][k]);
                    tmp->parent = c;
                    tmp->generated = false;
                    tmp->ics = new InnerCubeSeed();
                    if (k < gLvl) {
                        tmp->type = InnerCubeType::underground;
                    } else if (k == gLvl) {
                        tmp->type = InnerCubeType::midground;
                        tmp->ics->groundLevel = 5;
                    } else {
                        tmp->type = InnerCubeType::air;
                    }
                    fillInnerCube(tmp);
                    (*cubes)[i][j][k] = tmp;
                }
            }
        }
        c->cubes = cubes;
    }
}

void Map::fillInnerCube(InnerCube*& c) {
    if (c->type == InnerCubeType::midground) {
        c->generated = true;
        b3d* blocks = new b3d(ICS, b2d(ICS, b1d(ICS)));
        vector<Block*>* v = new vector<Block*>();
        c->visible = v;
        int gLvl = c->ics->groundLevel;

        for (int i = 0; i < ICS; ++i) {
            for (int j = 0; j < ICS; ++j) {
                for (int k = 0; k < ICS; ++k) {
                    Block* tmp;
                    if (k < gLvl) {
                        tmp = new Dirt();
                    } else if (k == gLvl) {
                        tmp = new Dirt();
                        c->visible->push_back(tmp);
                    } else {
                        tmp = new Air();
                    }
                    tmp->x = i;
                    tmp->y = j;
                    tmp->z = k;
                    tmp->parent = c;
                    tmp->pos = &(Lookup[i][j][k]);
                    (*blocks)[i][j][k] = tmp;
                }
            }
        }
        c->blocks = blocks;
    }
}

void Map::addPlayer(Player* p) {
    p->setMap(this);
    players.push_back(p);
    ascend(p);
}

void Map::sendLogs() {
    for (Player* p : players) {
        p->sendLog();
    }
}

void Map::generateBlockConstInfo() {
    Lookup = new string**[ICS];
    for (int i = 0; i < ICS; ++i) {
        Lookup[i] = new string*[ICS];
        for (int j = 0; j < ICS; ++j) {
            Lookup[i][j] = new string[ICS];
            for (int k = 0; k < ICS; ++k) {
                Lookup[i][j][k] = to_string(i) + to_string(j) + to_string(k);
            }
        }
    }
}
