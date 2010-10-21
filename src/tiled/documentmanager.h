/*
 * documentmanager.h
 * Copyright 2010, Stefan Beller <stefanbeller@googlemail.com>
 *
 * This file is part of Tiled.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef DOCUMENT_MANAGER_H
#define DOCUMENT_MANAGER_H

#include <QList>
#include <QPair>
#include <QTabWidget>
#include <QCoreApplication>

#include "mapview.h"
#include "mapscene.h"
#include "mapdocument.h"

namespace Tiled {

class Tileset;

namespace Internal {

class MapDocument;
class MapScene;
class MapView;

/**
 * This class controls the open documents.
 */
class DocumentManager : public QTabWidget
{
    Q_OBJECT

public:
    DocumentManager(QWidget *parent);
    ~DocumentManager();

    /**
     * Returns the current map document, the map view and the map scene
     */
    MapDocument *currentMapDocument() const;

    MapView *currentMapView() const;

    MapScene *currentMapScene() const;

    /**
     * Returns the number of mapdocuments.
     */
    int mapDocumentCount() const;

    /**
     * Adds a new or an opened MapDocument to this Manager
     * as parameter, only the mapDocument needs to be given.
     * the mapView, QWidget Tab and so on will be created by this manager
     */
    void addMapDocument(MapDocument *mapDocument);

    /**
     * Deletes/frees the current mapdocument. There is no questionaire, if
     * changes should be saved.
     */
    void closeMapDocument();

    /**
     * Close all documents. Even here will be no questionaire, wether to save
     * anything.
     */
    void closeMapDocuments();

    /**
     * Returns all MapDocuments.
     * when there is an empty tab (having a null pointer as Mapdocument)
     * an empty list will be returned.
     */
    QList<MapDocument*> mapDocuments() const;

    /**
     * This will rename the current opened tab.
     */
    void mapDocumentsFileNameChanged();

public slots:
    /**
     * Set the selected tool of the current active map
     */
    void setSelectedTool(AbstractTool *tool);

private slots:
    /**
     * This slot function switches to another MapDocument;
     * This should be connected to the QTabWidget in mainwindow.ui
     */
    void switchToMapDocument(int index);

signals:
    /**
     * Emitted when the current displayed MapDocument changed.
     */
    void currentMapDocumentChanged();

private:
    /**
     * This stores references to map scenes and map views.
     * These map scenes have pointers to the corresponding map documents.
     * To make sure there is always a map view available,
     * this data structure should be initialized with a Pair of
     * (new MapScene(this), new MapView()));
     * The map views need to have to set the scene to the
     * corresponding MapScene of course.
     */
    QList<QPair<MapScene*,MapView*> > mMaps;

    /**
     * When there is no document loaded there is still an empty view.
     * This bool tells you, if there is a tab with this empty view.
     */
    bool emptyView;
    AbstractTool *mActiveTool;
    int mIndex;
    QString mUntitledFileName;
};

} // namespace Tiled::Internal
} // namespace Tiled

#endif // DOCUMENT_MANAGER_H