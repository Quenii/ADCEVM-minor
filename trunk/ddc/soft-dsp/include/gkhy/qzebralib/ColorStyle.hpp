#include "gkhy/qzebralib/qzebra_lib_global.hpp"
#include <QWidget>
#include <QPointer>

namespace gkhy
{
	namespace QZebraLib
	{
		// not exported
		/*class StyleStore : public QObject
		{
			Q_OBJECT

		public:
			StyleStore(QObject* parent) : QObject(parent) {}
			virtual ~StyleStore() {}

			QString style() { return styleStr; }
			void setStyle(QString& str) { styleStr = str; }

		private:
			QString styleStr;
		};*/

		class QZEBRA_LIB_EXPORT ColorStyle
		{			
		public:
			enum StyleType
			{
				Normal,
				Red,
				Yellow,
				Green
			};

		public:
			ColorStyle(QWidget* widget) : widgetPtr(widget) {}
			virtual ~ColorStyle() {}
		private:
			Q_DISABLE_COPY(ColorStyle)
		public:
			void setStyle(StyleType type);
			//QWidget* widget() { return widgetPtr; }

		private:
			/*QString* stored();			
			void store();	
			void restore(QString* ptr = 0);*/
			
		private:
			QPointer<QWidget> widgetPtr;
		};	
	}
}