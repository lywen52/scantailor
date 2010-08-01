/*
    Scan Tailor - Interactive post-processing tool for scanned pages.
    Copyright (C)  Joseph Artsimovich <joseph.artsimovich@gmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef OUTPUT_DEWARPING_VIEW_H_
#define OUTPUT_DEWARPING_VIEW_H_

#include "ImageViewBase.h"
#include "ImagePixmapUnion.h"
#include "InteractionHandler.h"
#include "InteractiveBSpline.h"
#include "DragHandler.h"
#include "ZoomHandler.h"
#include "DistortionModel.h"
#include "DepthPerception.h"
#include "Settings.h"
#include "PageId.h"
#include <QTransform>
#include <QPointF>
#include <QRectF>

class QPolygonF;

namespace output
{

class DewarpingView : public ImageViewBase, protected InteractionHandler
{
	Q_OBJECT
public:
	DewarpingView(
		QImage const& image, ImagePixmapUnion const& downscaled_image,
		QTransform const& source_to_virt, QPolygonF const& virt_display_area,
		QRectF const& virt_content_rect, PageId const& page_id,
		IntrusivePtr<Settings> const& settings,
		DistortionModel const& distortion_model,
		DepthPerception const& depth_perception);
	
	virtual ~DewarpingView();
public slots:
	void depthPerceptionChanged(double val);	
protected:
	virtual void onPaint(QPainter& painter, InteractionState const& interaction);
private:
	void paintBSpline(
		QPainter& painter, InteractionState const& interaction,
		InteractiveBSpline const& ispline);

	void curveModified(int curve_idx);

	void dragFinished();

	QPointF sourceToWidget(QPointF const& pt) const;

	QPointF widgetToSource(QPointF const& pt) const;

	PageId m_pageId;
	DistortionModel m_distortionModel;
	DepthPerception m_depthPerception;
	IntrusivePtr<Settings> m_ptrSettings;
	InteractiveBSpline m_topSpline;
	InteractiveBSpline m_bottomSpline;
	DragHandler m_dragHandler;
	ZoomHandler m_zoomHandler;
	
};

} // namespace output

#endif
