﻿
Процедура ОбработкаПроведения(Отказ, Режим)
	//{{__КОНСТРУКТОР_ДВИЖЕНИЙ_РЕГИСТРОВ
	// Данный фрагмент построен конструктором.
	// При повторном использовании конструктора, внесенные вручную изменения будут утеряны!!!

	// регистр Продажи 
	Движения.Продажи.Записывать = Истина;
	Для Каждого ТекСтрокаТаблицаАктВыполненныхРабот Из ТаблицаАктВыполненныхРабот Цикл
		Движение = Движения.Продажи.Добавить();
		Движение.Период = Дата;
		Движение.Клиент = Клиент;
		Движение.Абонемент = ТекСтрокаТаблицаАктВыполненныхРабот.Абонемент;
		Движение.ВидСпорта = ТекСтрокаТаблицаАктВыполненныхРабот.ВидСпорта;
		Движение.Стоимость = ТекСтрокаТаблицаАктВыполненныхРабот.ИтоговаяСтоимостьРублей;
	КонецЦикла;

	//}}__КОНСТРУКТОР_ДВИЖЕНИЙ_РЕГИСТРОВ
КонецПроцедуры
