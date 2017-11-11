function b = appartenancePointTruc(Pt, Truc, nb)
    b = ( Truc(1:nb) * [Pt(1:nb-1) 1]' == 0 )
endfunction

function b = appartenancePointPlan(Pt, Pl)
    b = appartenancePointTruc(Pt, Pl, 4)
endfunction

function b = appartenancePointDroite(Pt, Dt)
    b = appartenancePointTruc(Pt, Dt, 3)
endfunction

function nb = rand_arrondi(nb)
    nb = floor(rand()*nb)/nb
endfunction

function cpt = testRand()
    xpoly([], [], "marks");
    prand=gce();
    pas = 1;
    cpt = 0;
    droite = [1 1 0]
    prec=0.01
    x = (0:prec:1)
    plot2d(x, (x.*droite(1)+droite(3))./droite(2))
    for i = 0 : pas : 20000
        point = [rand_arrondi(1/prec) rand_arrondi(1/prec)]
        if(appartenancePointDroite(point, droite)) then
            cpt = cpt + 1;
        end
        prand.data = [prand.data; point];
    end
endfunction
